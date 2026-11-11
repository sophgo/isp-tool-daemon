#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

/*
 * File operations for the file transport daemon.
 * All paths are relative to a root_dir set at init time.
 */

/* Initialize file ops with a root directory. Returns 0 on success, -1 on error.
 */
int file_ops_init(const char *root_dir);

/* Get the resolved root directory path. */
const char *file_ops_root(void);

/*
 * Resolve a client-supplied relative path to an absolute path under root.
 * Returns 0 on success, -1 if the path escapes root or is invalid.
 * resolved must be at least PATH_MAX bytes.
 */
int file_ops_resolve(const char *rel_path, char *resolved, size_t resolved_size);

/*
 * Populate buffer with LIST_RSP payload for the given relative directory path.
 * Returns number of bytes written to buf, or -1 on error.
 * If buf is NULL, returns the required size.
 */
ssize_t file_ops_list_dir(const char *rel_path, uint8_t *buf, size_t buf_size);

/*
 * Download: read file in chunks. For each chunk, callback is invoked with
 * (offset, data, len, user). callback should send the chunk to the client.
 * Returns 0 on success, -1 on error.
 */
typedef int (*chunk_send_fn)(uint64_t offset, const uint8_t *data, size_t len,
			     void *user);
int file_ops_download_file(const char *rel_path, chunk_send_fn callback,
			   void *user);

/*
 * Upload: write a chunk at given offset.
 * Returns 0 on success, -1 on error.
 */
int file_ops_upload_chunk(const char *rel_path, uint64_t offset,
			  const uint8_t *data, size_t len);

/* Create directory with 0755. Returns 0 on success, -1 on error. */
int file_ops_create_dir(const char *rel_path);

/* Delete file or empty directory. Returns 0 on success, -1 on error. */
int file_ops_delete_path(const char *rel_path);

/* Get file size. Returns size on success, -1 on error. */
int64_t file_ops_get_file_size(const char *rel_path);

/* Map errno to FTP error code */
int file_ops_errno_to_ftp(int err);

#endif /* FILE_OPS_H */
