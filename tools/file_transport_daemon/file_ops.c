#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include "file_ops.h"
#include "protocol.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char g_root[PATH_MAX];
static size_t g_root_len;

/*
 * Safe path join: writes "base/name" into dst (size dst_size).
 * Returns 0 on success, -1 if result would be truncated.
 */
static int path_join(char *dst, size_t dst_size, const char *base,
		     const char *name)
{
	size_t blen = strlen(base);
	size_t nlen = strlen(name);

	/* Need blen + '/' + nlen + '\0' */
	if (blen + 1 + nlen + 1 > dst_size)
		return -1;
	memcpy(dst, base, blen);
	dst[blen] = '/';
	memcpy(dst + blen + 1, name, nlen);
	dst[blen + 1 + nlen] = '\0';
	return 0;
}

int file_ops_init(const char *root_dir)
{
	g_root[0] = '\0';
	g_root_len = 0;

	if (!root_dir || !root_dir[0]) {
		/* No root_dir - allow access to any path (no restriction) */
		return 0;
	}

	if (!realpath(root_dir, g_root))
		return -1;

	g_root_len = strlen(g_root);
	return 0;
}

const char *file_ops_root(void)
{
	return g_root;
}

int file_ops_resolve(const char *client_path, char *resolved,
		     size_t resolved_size)
{
	char full[PATH_MAX];
	char tmp[PATH_MAX];
	struct stat st;

	if (!client_path || !resolved) {
		errno = EINVAL;
		return -1;
	}

	/* Reject ".." anywhere in the path */
	if (strstr(client_path, "..")) {
		errno = EINVAL;
		return -1;
	}

	/* Build absolute path */
	if (client_path[0] == '/') {
		/* Absolute path from client */
		if (strlen(client_path) >= sizeof(full))
			return -1;
		strcpy(full, client_path);
	} else if (client_path[0] == '\0') {
		/* Empty path - use root or cwd */
		if (g_root[0]) {
			strcpy(full, g_root);
		} else {
			if (!getcwd(full, sizeof(full)))
				return -1;
		}
	} else {
		/* Relative path - resolve against root or cwd */
		const char *base = g_root[0] ? g_root : ".";

		if (path_join(full, sizeof(full), base, client_path) != 0)
			return -1;
	}

	/*
	 * For paths that may not exist yet (upload, mkdir), resolve the parent
	 * and append the basename.
	 */
	if (stat(full, &st) == 0) {
		/* Path exists - use realpath directly */
		if (!realpath(full, tmp))
			return -1;
	} else {
		/* Path doesn't exist yet - resolve parent */
		char *slash = strrchr(full, '/');

		if (!slash) {
			/* Shouldn't happen since we built full as absolute path */
			return -1;
		} else if (slash == full) {
			/* Parent is "/" */
			if (path_join(tmp, sizeof(tmp), "/", slash + 1) != 0)
				return -1;
		} else {
			char parent[PATH_MAX];
			char resolved_parent[PATH_MAX];
			size_t plen = (size_t)(slash - full);

			if (plen >= sizeof(parent))
				return -1;
			memcpy(parent, full, plen);
			parent[plen] = '\0';

			if (!realpath(parent, resolved_parent))
				return -1;

			if (path_join(tmp, sizeof(tmp), resolved_parent,
				      slash + 1) != 0)
				return -1;
		}
	}

	/* If root_dir is set, verify the resolved path is under it */
	if (g_root[0]) {
		if (strncmp(tmp, g_root, g_root_len) != 0 ||
		    (tmp[g_root_len] != '\0' && tmp[g_root_len] != '/')) {
			errno = EACCES;
			return -1;
		}
	}

	if (strlen(tmp) >= resolved_size)
		return -1;

	strcpy(resolved, tmp);
	return 0;
}

int file_ops_errno_to_ftp(int err)
{
	switch (err) {
	case ENOENT:
		return FTP_ERR_ENOENT;
	case EACCES:
		return FTP_ERR_EACCES;
	case EIO:
		return FTP_ERR_EIO;
	case EINVAL:
		return FTP_ERR_EINVAL;
	case ENOMEM:
		return FTP_ERR_ENOMEM;
	default:
		return FTP_ERR_EIO;
	}
}

ssize_t file_ops_list_dir(const char *rel_path, uint8_t *buf, size_t buf_size)
{
	char resolved[PATH_MAX];
	DIR *dir;
	struct dirent *ent;
	size_t offset = 0;

	if (file_ops_resolve(rel_path, resolved, sizeof(resolved)) != 0)
		return -1;

	dir = opendir(resolved);
	if (!dir)
		return -1;

	while ((ent = readdir(dir)) != NULL) {
		const char *name;
		uint32_t name_len;
		uint8_t flags = 0;
		uint64_t file_size = 0;
		uint64_t mtime = 0;
		char entry_path[PATH_MAX];
		struct stat st;
		size_t entry_size;

		/* Skip . and .. */
		if (strcmp(ent->d_name, ".") == 0 ||
		    strcmp(ent->d_name, "..") == 0)
			continue;

		name = ent->d_name;
		name_len = (uint32_t)strlen(name);

		/* Build full path for stat */
		if (path_join(entry_path, sizeof(entry_path),
			      resolved, name) != 0)
			continue; /* name too long, skip */

		if (stat(entry_path, &st) == 0) {
			if (S_ISDIR(st.st_mode))
				flags |= FTP_FLAG_IS_DIR;
			if (name[0] == '.')
				flags |= FTP_FLAG_IS_HIDDEN;
			file_size = (uint64_t)st.st_size;
			mtime = (uint64_t)st.st_mtime;
		} else {
			/* Can't stat - skip entry rather than fail */
			continue;
		}

		/* Entry size: 4 (name_len) + name_len + 1 (flags) + 8 + 8 */
		entry_size = 4 + name_len + 1 + 8 + 8;

		if (buf) {
			if (offset + entry_size > buf_size) {
				closedir(dir);
				return -1;
			}
			ftp_put_u32(buf + offset, name_len);
			offset += 4;
			memcpy(buf + offset, name, name_len);
			offset += name_len;
			buf[offset] = flags;
			offset += 1;
			ftp_put_u64(buf + offset, file_size);
			offset += 8;
			ftp_put_u64(buf + offset, mtime);
			offset += 8;
		} else {
			offset += entry_size;
		}
	}

	closedir(dir);
	return (ssize_t)offset;
}

int file_ops_download_file(const char *rel_path, chunk_send_fn callback,
			   void *user)
{
	char resolved[PATH_MAX];
	int fd;
	uint8_t chunk[FTP_CHUNK_SIZE];
	uint64_t offset = 0;
	int ret = 0;

	if (file_ops_resolve(rel_path, resolved, sizeof(resolved)) != 0)
		return -1;

	fd = open(resolved, O_RDONLY);
	if (fd < 0)
		return -1;

	for (;;) {
		ssize_t n = read(fd, chunk, sizeof(chunk));

		if (n < 0) {
			if (errno == EINTR)
				continue;
			ret = -1;
			break;
		}
		if (n == 0)
			break;

		if (callback(offset, chunk, (size_t)n, user) != 0) {
			ret = -1;
			break;
		}
		offset += (uint64_t)n;
	}

	close(fd);
	return ret;
}

int file_ops_upload_chunk(const char *rel_path, uint64_t offset,
			  const uint8_t *data, size_t len)
{
	char resolved[PATH_MAX];
	int fd;
	size_t written = 0;

	if (file_ops_resolve(rel_path, resolved, sizeof(resolved)) != 0)
		return -1;

	fd = open(resolved, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return -1;

	if (lseek(fd, (off_t)offset, SEEK_SET) < 0) {
		close(fd);
		return -1;
	}

	while (written < len) {
		ssize_t n = write(fd, data + written, len - written);

		if (n < 0) {
			if (errno == EINTR)
				continue;
			close(fd);
			return -1;
		}
		written += (size_t)n;
	}

	close(fd);
	return 0;
}

int file_ops_create_dir(const char *rel_path)
{
	char resolved[PATH_MAX];

	if (file_ops_resolve(rel_path, resolved, sizeof(resolved)) != 0)
		return -1;

	return mkdir(resolved, 0755);
}

int file_ops_delete_path(const char *rel_path)
{
	char resolved[PATH_MAX];
	struct stat st;

	if (file_ops_resolve(rel_path, resolved, sizeof(resolved)) != 0)
		return -1;

	if (stat(resolved, &st) != 0)
		return -1;

	if (S_ISDIR(st.st_mode))
		return rmdir(resolved);

	return unlink(resolved);
}

int64_t file_ops_get_file_size(const char *rel_path)
{
	char resolved[PATH_MAX];
	struct stat st;

	if (file_ops_resolve(rel_path, resolved, sizeof(resolved)) != 0)
		return -1;

	if (stat(resolved, &st) != 0)
		return -1;

	return (int64_t)st.st_size;
}
