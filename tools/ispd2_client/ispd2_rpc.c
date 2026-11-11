/*
 * ispd2_rpc — TCP transport for the isp daemon2 JSON-RPC interface.
 *
 * Wire protocol (verified against modules/isp/cv184x/isp-daemon2/src/
 * cvi_ispd2_message.c): requests and replies are bare JSON texts with no
 * length prefix and no terminator; a message ends when its bracket depth
 * returns to zero outside of any string. Binary replies (dump/bin data)
 * are preceded by a JSON reply whose "Data size" field announces the
 * exact byte count that follows; the daemon sends the 4 ASCII bytes
 * "NONE" when there is nothing to stream.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "cvi_json_object.h"
#include "cvi_json_tokener.h"

#include "ispd2_rpc.h"

#define ISPD2_RECV_TIMEOUT_SEC	(10)
#define ISPD2_CHUNK		(64 * 1024)

/* ---- protocol logging ------------------------------------------------- */
static FILE *g_log_file;
static int g_verbose;

int ispd2_open_log(const char *path)
{
	if (!path)
		return 0;
	if (g_log_file && g_log_file != stdout)
		fclose(g_log_file);
	g_log_file = fopen(path, "w");
	if (!g_log_file) {
		ISPD2_CLI_PRT("open log %s failed: %s\n", path, strerror(errno));
		return -1;
	}
	return 0;
}

void ispd2_close_log(void)
{
	if (g_log_file && g_log_file != stdout) {
		fclose(g_log_file);
		g_log_file = NULL;
	}
}

void ispd2_set_verbose(int on)
{
	g_verbose = on ? 1 : 0;
}

void ispd2_rpc_log(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	if (g_log_file) {
		va_list ap2;

		va_copy(ap2, ap);
		vfprintf(g_log_file, fmt, ap2);
		va_end(ap2);
		fflush(g_log_file);
	}
	if (g_verbose)
		vprintf(fmt, ap);
	va_end(ap);
}

static int g_fd = -1;
static int g_id;

/* framing state: unscanned bytes live in g_buf[g_scan .. g_buf_len) */
static unsigned char *g_buf;
static size_t g_buf_cap;
static size_t g_buf_len;
static size_t g_scan;
static int g_depth;	/* { [ nesting outside strings */
static int g_in_str;	/* inside "..." */
static int g_esc;	/* previous char was backslash */

static int _write_all(const unsigned char *buf, size_t n)
{
	size_t off = 0;

	while (off < n) {
		ssize_t w = write(g_fd, buf + off, n - off);

		if (w < 0) {
			if (errno == EINTR)
				continue;
			ISPD2_CLI_PRT("write failed: %s\n", strerror(errno));
			return -1;
		}
		off += (size_t)w;
	}

	return 0;
}

int ispd2_connect(const char *ip, int port)
{
	struct sockaddr_in addr;
	struct timeval tv;

	if (g_fd >= 0) {
		ISPD2_CLI_PRT("already connected\n");
		return -1;
	}

	g_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (g_fd < 0) {
		ISPD2_CLI_PRT("socket failed: %s\n", strerror(errno));
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons((uint16_t)port);
	if (inet_pton(AF_INET, ip, &addr.sin_addr) != 1) {
		ISPD2_CLI_PRT("invalid ip '%s'\n", ip);
		close(g_fd);
		g_fd = -1;
		return -1;
	}

	if (connect(g_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		ISPD2_CLI_PRT("connect %s:%d failed: %s\n", ip, port, strerror(errno));
		close(g_fd);
		g_fd = -1;
		return -1;
	}

	tv.tv_sec = ISPD2_RECV_TIMEOUT_SEC;
	tv.tv_usec = 0;
	setsockopt(g_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

	g_id = 0;
	return 0;
}

void ispd2_close(void)
{
	if (g_fd >= 0) {
		close(g_fd);
		g_fd = -1;
	}

	free(g_buf);
	g_buf = NULL;
	g_buf_cap = 0;
	g_buf_len = 0;
	g_scan = 0;
	g_depth = 0;
	g_in_str = 0;
	g_esc = 0;
}

int ispd2_send_request(const char *method, struct cvi_json_object *params)
{
	struct cvi_json_object *req;
	const char *str;

	if (g_fd < 0) {
		ISPD2_CLI_PRT("not connected\n");
		if (params)
			cvi_json_object_put(params);
		return -1;
	}

	req = cvi_json_object_new_object();
	cvi_json_object_object_add(req, "jsonrpc", cvi_json_object_new_string("2.0"));
	cvi_json_object_object_add(req, "method", cvi_json_object_new_string(method));
	cvi_json_object_object_add(req, "id", cvi_json_object_new_int(++g_id));
	if (params)
		cvi_json_object_object_add(req, "params", params);	/* ref stolen here */

	str = cvi_json_object_to_cvi_json_string_ext(req, JSON_C_TO_STRING_PLAIN);
	ispd2_rpc_log("[ispd2_cli] >> %s\n", str);

	if (_write_all((const unsigned char *)str, strlen(str)) != 0) {
		cvi_json_object_put(req);
		return -1;
	}

	cvi_json_object_put(req);
	return 0;
}

int ispd2_send_binary(const unsigned char *buf, size_t n)
{
	if (g_fd < 0) {
		ISPD2_CLI_PRT("not connected\n");
		return -1;
	}

	return _write_all(buf, n);
}

static int _buf_append(const unsigned char *data, size_t n)
{
	if (g_buf_len + n > g_buf_cap) {
		size_t cap = g_buf_cap ? g_buf_cap : (2 * ISPD2_CHUNK);
		unsigned char *p;

		while (cap < g_buf_len + n)
			cap *= 2;
		p = realloc(g_buf, cap);
		if (!p) {
			ISPD2_CLI_PRT("realloc failed\n");
			return -1;
		}
		g_buf = p;
		g_buf_cap = cap;
	}

	memcpy(g_buf + g_buf_len, data, n);
	g_buf_len += n;
	return 0;
}

static void _buf_drop(size_t n)
{
	memmove(g_buf, g_buf + n, g_buf_len - n);
	g_buf_len -= n;
}

struct cvi_json_object *ispd2_recv_reply(void)
{
	if (g_fd < 0) {
		ISPD2_CLI_PRT("not connected\n");
		return NULL;
	}

	for (;;) {
		unsigned char chunk[ISPD2_CHUNK];
		ssize_t r;
		size_t i;

		/* scan unscanned bytes for end-of-message */
		for (i = g_scan; i < g_buf_len; i++) {
			unsigned char c = g_buf[i];

			if (g_in_str) {
				if (g_esc) {
					g_esc = 0;
				} else if (c == '\\') {
					g_esc = 1;
				} else if (c == '"') {
					g_in_str = 0;
				}
				continue;
			}

			if (c == '"') {
				g_in_str = 1;
			} else if (c == '{' || c == '[') {
				g_depth++;
			} else if (c == '}' || c == ']') {
				g_depth--;
				if (g_depth == 0) {
					/* message = g_buf[0 .. i] inclusive */
					char *msg = malloc(i + 2);
					struct cvi_json_object *obj;

					if (!msg) {
						ISPD2_CLI_PRT("malloc failed\n");
						return NULL;
					}
					memcpy(msg, g_buf, i + 1);
					msg[i + 1] = '\0';

					_buf_drop(i + 1);
					g_scan = 0;
					g_depth = 0;
					g_in_str = 0;
					g_esc = 0;

					ispd2_rpc_log("[ispd2_cli] << %s\n", msg);
					obj = cvi_json_tokener_parse(msg);
					if (!obj)
						ISPD2_CLI_PRT("reply is not valid JSON\n");
					free(msg);
					return obj;
				}
			}
		}
		g_scan = g_buf_len;

		r = read(g_fd, chunk, sizeof(chunk));
		if (r < 0) {
			if (errno == EINTR)
				continue;
			ISPD2_CLI_PRT("read failed: %s\n", strerror(errno));
			return NULL;
		}
		if (r == 0) {
			ISPD2_CLI_PRT("connection closed by peer\n");
			return NULL;
		}
		if (_buf_append(chunk, (size_t)r) != 0)
			return NULL;
	}
}

static int _recv_exact(unsigned char *buf, size_t n)
{
	size_t off = 0;

	while (off < n) {
		ssize_t r = read(g_fd, buf + off, n - off);

		if (r < 0) {
			if (errno == EINTR)
				continue;
			ISPD2_CLI_PRT("read failed: %s\n", strerror(errno));
			return -1;
		}
		if (r == 0) {
			ISPD2_CLI_PRT("connection closed by peer\n");
			return -1;
		}
		off += (size_t)r;
	}

	return 0;
}

int ispd2_recv_binary(size_t n, unsigned char **out)
{
	unsigned char head[4];
	unsigned char *buf;

	*out = NULL;
	if (g_fd < 0 || n == 0) {
		ISPD2_CLI_PRT("bad args (fd=%d n=%zu)\n", g_fd, n);
		return -1;
	}

	if (n >= 4) {
		/* daemon sends 4 ASCII bytes "NONE" when there is no data */
		if (_recv_exact(head, 4) != 0)
			return -1;
		if (memcmp(head, "NONE", 4) == 0) {
			ISPD2_CLI_PRT("daemon has no data (NONE)\n");
			return 1;
		}
	}

	buf = malloc(n);
	if (!buf) {
		ISPD2_CLI_PRT("malloc %zu failed\n", n);
		return -1;
	}
	if (n >= 4)
		memcpy(buf, head, 4);
	if (_recv_exact(buf + (n >= 4 ? 4 : 0), n - (n >= 4 ? 4 : 0)) != 0) {
		free(buf);
		return -1;
	}
	*out = buf;
	return 0;
}
