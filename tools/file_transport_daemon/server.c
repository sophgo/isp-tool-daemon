#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include "server.h"
#include "protocol.h"
#include "file_ops.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static sig_atomic_t g_running = 1;

/* Upload session state (single-client) */
static char g_upload_path[PATH_MAX];
static int g_upload_active;

void server_set_running(int val)
{
	g_running = val;
}

/* ---- Send helpers ---- */

static int send_all(int fd, const uint8_t *buf, size_t len)
{
	size_t sent = 0;

	while (sent < len) {
		ssize_t n = send(fd, buf + sent, len - sent, MSG_NOSIGNAL);

		if (n < 0) {
			if (errno == EINTR)
				continue;
			return -1;
		}
		sent += (size_t)n;
	}
	return 0;
}

static int send_header(int fd, uint32_t cmd, uint32_t seq, uint32_t payload_len)
{
	uint8_t hdr[FTP_HEADER_SIZE];

	hdr[0] = FTP_MAGIC_0;
	hdr[1] = FTP_MAGIC_1;
	hdr[2] = FTP_MAGIC_2;
	hdr[3] = FTP_MAGIC_3;
	ftp_put_u32(hdr + 4, cmd);
	ftp_put_u32(hdr + 8, seq);
	ftp_put_u32(hdr + 12, payload_len);
	return send_all(fd, hdr, FTP_HEADER_SIZE);
}

static int send_ack(int fd, uint32_t seq, uint32_t original_cmd)
{
	uint8_t payload[4];

	ftp_put_u32(payload, original_cmd);
	if (send_header(fd, FTP_CMD_ACK, seq, 4) != 0)
		return -1;
	return send_all(fd, payload, 4);
}

static int send_error(int fd, uint32_t seq, uint32_t original_cmd,
			  uint32_t error_code, const char *msg)
{
	uint32_t msg_len = msg ? (uint32_t)strlen(msg) : 0;
	uint32_t payload_len = 4 + 4 + msg_len;
	uint8_t *payload = malloc(payload_len);

	if (!payload)
		return -1;

	ftp_put_u32(payload, original_cmd);
	ftp_put_u32(payload + 4, error_code);
	if (msg_len > 0)
		memcpy(payload + 8, msg, msg_len);

	int ret = 0;

	if (send_header(fd, FTP_CMD_ERROR_RSP, seq, payload_len) != 0)
		ret = -1;
	else if (send_all(fd, payload, payload_len) != 0)
		ret = -1;

	free(payload);
	return ret;
}

/* ---- Read helpers ---- */

static int recv_all(int fd, uint8_t *buf, size_t len)
{
	size_t got = 0;

	while (got < len) {
		ssize_t n = recv(fd, buf + got, len - got, 0);

		if (n < 0) {
			if (errno == EINTR)
				continue;
			return -1;
		}
		if (n == 0)
			return -1; /* connection closed */
		got += (size_t)n;
	}
	return 0;
}

static int read_header(int fd, struct ftp_header *hdr)
{
	uint8_t buf[FTP_HEADER_SIZE];

	if (recv_all(fd, buf, FTP_HEADER_SIZE) != 0)
		return -1;

	if (buf[0] != FTP_MAGIC_0 || buf[1] != FTP_MAGIC_1 ||
	    buf[2] != FTP_MAGIC_2 || buf[3] != FTP_MAGIC_3)
		return -1;

	hdr->cmd = ftp_get_u32(buf + 4);
	hdr->seq = ftp_get_u32(buf + 8);
	hdr->payload_len = ftp_get_u32(buf + 12);
	return 0;
}

static uint8_t *read_payload(int fd, uint32_t len)
{
	if (len == 0)
		return NULL;

	/* Cap payload at 16 MB to prevent abuse */
	if (len > 16U * 1024U * 1024U)
		return NULL;

	uint8_t *buf;

	buf = malloc(len);
	if (!buf)
		return NULL;

	if (recv_all(fd, buf, len) != 0) {
		free(buf);
		return NULL;
	}
	return buf;
}

/* ---- Extract null-terminated path from payload ---- */

static int extract_path(const uint8_t *payload, uint32_t payload_len,
			char *out, size_t out_size)
{
	if (payload_len == 0 || payload_len >= out_size)
		return -1;
	memcpy(out, payload, payload_len);
	out[payload_len] = '\0';
	return 0;
}

/* ---- Command handlers ---- */

static void handle_list_req(int fd, const struct ftp_header *hdr, const uint8_t *payload)
{
	char path[PATH_MAX];

	if (hdr->payload_len == 0) {
		path[0] = '\0';
	} else {
		if (extract_path(payload, hdr->payload_len, path, sizeof(path)) != 0) {
			send_error(fd, hdr->seq, hdr->cmd, FTP_ERR_EINVAL, "path too long");
			return;
		}
	}

	/* First call: get required size */
	ssize_t needed;

	needed = file_ops_list_dir(path, NULL, 0);
	if (needed < 0) {
		send_error(fd, hdr->seq, hdr->cmd,
			   file_ops_errno_to_ftp(errno), strerror(errno));
		return;
	}

	if (needed == 0) {
		send_header(fd, FTP_CMD_LIST_RSP, hdr->seq, 0);
		return;
	}

	uint8_t *buf;

	buf = malloc((size_t)needed);
	if (!buf) {
		send_error(fd, hdr->seq, hdr->cmd, FTP_ERR_ENOMEM, "out of memory");
		return;
	}

	ssize_t written;

	written = file_ops_list_dir(path, buf, (size_t)needed);
	if (written < 0) {
		free(buf);
		send_error(fd, hdr->seq, hdr->cmd,
			   file_ops_errno_to_ftp(errno), strerror(errno));
		return;
	}

	if (send_header(fd, FTP_CMD_LIST_RSP, hdr->seq, (uint32_t)written) != 0) {
		free(buf);
		return;
	}
	send_all(fd, buf, (size_t)written);
	free(buf);
}

/* Context for download callback */
struct download_ctx {
	int fd;
	uint32_t seq;
	int error;
};

static int download_send_chunk(uint64_t offset, const uint8_t *data, size_t len, void *user)
{
	struct download_ctx *ctx = (struct download_ctx *)user;

	if (ctx->error)
		return -1;

	/* payload: offset(8) + data(len) */
	uint32_t payload_len;

	payload_len = 8 + (uint32_t)len;
	if (send_header(ctx->fd, FTP_CMD_DOWNLOAD_CHUNK, ctx->seq, payload_len) != 0) {
		ctx->error = 1;
		return -1;
	}

	uint8_t off_buf[8];

	ftp_put_u64(off_buf, offset);
	if (send_all(ctx->fd, off_buf, 8) != 0) {
		ctx->error = 1;
		return -1;
	}
	if (send_all(ctx->fd, data, len) != 0) {
		ctx->error = 1;
		return -1;
	}
	return 0;
}

static void handle_download_req(int fd, const struct ftp_header *hdr, const uint8_t *payload)
{
	char path[PATH_MAX];

	if (extract_path(payload, hdr->payload_len, path, sizeof(path)) != 0) {
		send_error(fd, hdr->seq, hdr->cmd, FTP_ERR_EINVAL, "invalid path");
		return;
	}

	int64_t file_size;

	file_size = file_ops_get_file_size(path);
	if (file_size < 0) {
		send_error(fd, hdr->seq, hdr->cmd,
			   file_ops_errno_to_ftp(errno), strerror(errno));
		return;
	}

	struct download_ctx ctx;

	ctx.fd = fd;
	ctx.seq = hdr->seq;
	ctx.error = 0;

	if (file_ops_download_file(path, download_send_chunk, &ctx) != 0) {
		if (!ctx.error) {
			send_error(fd, hdr->seq, hdr->cmd,
				   file_ops_errno_to_ftp(errno), strerror(errno));
		}
		return;
	}

	/* Send DOWNLOAD_DONE with file_size */
	uint8_t done_payload[8];

	ftp_put_u64(done_payload, (uint64_t)file_size);
	if (send_header(fd, FTP_CMD_DOWNLOAD_DONE, hdr->seq, 8) != 0)
		return;
	send_all(fd, done_payload, 8);
}

static void handle_upload_req(int fd, const struct ftp_header *hdr, const uint8_t *payload)
{
	/* payload: file_size(8) + path */
	if (hdr->payload_len < 9) {
		send_error(fd, hdr->seq, hdr->cmd, FTP_ERR_EINVAL, "invalid upload request");
		return;
	}

	uint32_t path_len;

	path_len = hdr->payload_len - 8;
	if (path_len == 0 || path_len >= sizeof(g_upload_path)) {
		send_error(fd, hdr->seq, hdr->cmd, FTP_ERR_EINVAL, "invalid path");
		return;
	}
	memcpy(g_upload_path, payload + 8, path_len);
	g_upload_path[path_len] = '\0';

	char resolved[PATH_MAX];

	if (file_ops_resolve(g_upload_path, resolved, sizeof(resolved)) != 0) {
		send_error(fd, hdr->seq, hdr->cmd, FTP_ERR_EINVAL, "invalid path");
		return;
	}

	g_upload_active = 1;
	send_ack(fd, hdr->seq, hdr->cmd);
}

static void handle_upload_chunk(int fd, const struct ftp_header *hdr, const uint8_t *payload)
{
	if (!g_upload_active) {
		send_error(fd, hdr->seq, hdr->cmd, FTP_ERR_EINVAL, "no active upload");
		return;
	}

	if (hdr->payload_len < 8) {
		send_error(fd, hdr->seq, hdr->cmd, FTP_ERR_EINVAL, "invalid chunk");
		return;
	}

	uint64_t offset = ftp_get_u64(payload);
	const uint8_t *data = payload + 8;
	size_t data_len = hdr->payload_len - 8;

	if (file_ops_upload_chunk(g_upload_path, offset, data, data_len) != 0) {
		send_error(fd, hdr->seq, hdr->cmd,
			   file_ops_errno_to_ftp(errno), strerror(errno));
		return;
	}

	send_ack(fd, hdr->seq, hdr->cmd);
}

static void handle_upload_done(int fd, const struct ftp_header *hdr)
{
	if (!g_upload_active) {
		send_error(fd, hdr->seq, hdr->cmd, FTP_ERR_EINVAL, "no active upload");
		return;
	}
	g_upload_active = 0;
	send_ack(fd, hdr->seq, hdr->cmd);
}

static void handle_mkdir_req(int fd, const struct ftp_header *hdr, const uint8_t *payload)
{
	char path[PATH_MAX];

	if (extract_path(payload, hdr->payload_len, path, sizeof(path)) != 0) {
		send_error(fd, hdr->seq, hdr->cmd, FTP_ERR_EINVAL, "invalid path");
		return;
	}

	if (file_ops_create_dir(path) != 0) {
		send_error(fd, hdr->seq, hdr->cmd,
			   file_ops_errno_to_ftp(errno), strerror(errno));
		return;
	}

	send_ack(fd, hdr->seq, hdr->cmd);
}

static void handle_delete_req(int fd, const struct ftp_header *hdr, const uint8_t *payload)
{
	char path[PATH_MAX];

	if (extract_path(payload, hdr->payload_len, path, sizeof(path)) != 0) {
		send_error(fd, hdr->seq, hdr->cmd, FTP_ERR_EINVAL, "invalid path");
		return;
	}

	if (file_ops_delete_path(path) != 0) {
		send_error(fd, hdr->seq, hdr->cmd,
			   file_ops_errno_to_ftp(errno), strerror(errno));
		return;
	}

	send_ack(fd, hdr->seq, hdr->cmd);
}

/* ---- Main client handler ---- */

static void handle_client(int fd)
{
	printf("Client connected\n");

	while (g_running) {
		struct ftp_header hdr;

		if (read_header(fd, &hdr) != 0) {
			printf("Client disconnected or protocol error\n");
			break;
		}

		uint8_t *payload;

		payload = read_payload(fd, hdr.payload_len);
		if (hdr.payload_len > 0 && !payload) {
			printf("Failed to read payload (len=%u)\n", hdr.payload_len);
			break;
		}

		switch (hdr.cmd) {
		case FTP_CMD_LIST_REQ:
			handle_list_req(fd, &hdr, payload);
			break;
		case FTP_CMD_DOWNLOAD_REQ:
			handle_download_req(fd, &hdr, payload);
			break;
		case FTP_CMD_UPLOAD_REQ:
			handle_upload_req(fd, &hdr, payload);
			break;
		case FTP_CMD_UPLOAD_CHUNK:
			handle_upload_chunk(fd, &hdr, payload);
			break;
		case FTP_CMD_UPLOAD_DONE:
			handle_upload_done(fd, &hdr);
			break;
		case FTP_CMD_MKDIR_REQ:
			handle_mkdir_req(fd, &hdr, payload);
			break;
		case FTP_CMD_DELETE_REQ:
			handle_delete_req(fd, &hdr, payload);
			break;
		default:
			send_error(fd, hdr.seq, hdr.cmd, FTP_ERR_EINVAL, "unknown command");
			break;
		}

		free(payload);
	}

	g_upload_active = 0;
	printf("Client handler exiting\n");
}

/* ---- Server main loop ---- */

int server_run(int port, const char *root_dir)
{
	if (file_ops_init(root_dir) != 0) {
		fprintf(stderr, "Failed to initialize file ops with root: %s\n", root_dir);
		return -1;
	}

	int listen_fd;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0) {
		perror("socket");
		return -1;
	}

	int opt = 1;

	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons((uint16_t)port);

	if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		perror("bind");
		close(listen_fd);
		return -1;
	}

	if (listen(listen_fd, 1) != 0) {
		perror("listen");
		close(listen_fd);
		return -1;
	}

	printf("Listening on port %d, root: %s\n", port, file_ops_root());
	fflush(stdout);

	while (g_running) {
		fd_set rfds;

		FD_ZERO(&rfds);
		FD_SET(listen_fd, &rfds);

		struct timeval tv;

		tv.tv_sec = 1;
		tv.tv_usec = 0;

		int ret;

		ret = select(listen_fd + 1, &rfds, NULL, NULL, &tv);
		if (ret < 0) {
			if (errno == EINTR)
				continue;
			perror("select");
			break;
		}
		if (ret == 0)
			continue;

		struct sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);
		int client_fd;

		client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
		if (client_fd < 0) {
			if (errno == EINTR)
				continue;
			perror("accept");
			continue;
		}

		printf("Accepted connection from %s:%d\n",
			   inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		fflush(stdout);

		handle_client(client_fd);

		close(client_fd);
	}

	close(listen_fd);
	printf("Server shutting down\n");
	return 0;
}
