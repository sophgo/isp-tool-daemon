#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

/*
 * File Transport Protocol
 * All integers are BIG-ENDIAN (network byte order).
 *
 * Header (16 bytes, fixed):
 *   magic[4]:    'F','T','P','T'
 *   cmd:         uint32_t
 *   seq:         uint32_t
 *   payload_len: uint32_t
 *
 * Payload follows, length = payload_len.
 */

#define FTP_MAGIC_0 0x46
#define FTP_MAGIC_1 0x54
#define FTP_MAGIC_2 0x50
#define FTP_MAGIC_3 0x54

#define FTP_HEADER_SIZE 16
#define FTP_CHUNK_SIZE  65536  /* 64 KB */

/* Commands */
#define FTP_CMD_LIST_REQ       0x01
#define FTP_CMD_LIST_RSP       0x02
#define FTP_CMD_DOWNLOAD_REQ   0x03
#define FTP_CMD_DOWNLOAD_CHUNK 0x04
#define FTP_CMD_DOWNLOAD_DONE  0x05
#define FTP_CMD_UPLOAD_REQ     0x06
#define FTP_CMD_UPLOAD_CHUNK   0x07
#define FTP_CMD_UPLOAD_DONE    0x08
#define FTP_CMD_MKDIR_REQ      0x09
#define FTP_CMD_DELETE_REQ     0x0A
#define FTP_CMD_ACK            0x10
#define FTP_CMD_ERROR_RSP      0x11

/* Error codes */
#define FTP_ERR_ENOENT  1
#define FTP_ERR_EACCES  2
#define FTP_ERR_EIO     3
#define FTP_ERR_EINVAL  4
#define FTP_ERR_ENOMEM  5

/* LIST_RSP entry flags */
#define FTP_FLAG_IS_DIR    0x01
#define FTP_FLAG_IS_HIDDEN 0x02

#pragma pack(push, 1)

struct ftp_header {
	uint8_t  magic[4];
	uint32_t cmd;
	uint32_t seq;
	uint32_t payload_len;
};

#pragma pack(pop)

/* Helper: write uint32 big-endian into buffer */
static inline void ftp_put_u32(uint8_t *buf, uint32_t val)
{
	buf[0] = (uint8_t)(val >> 24);
	buf[1] = (uint8_t)(val >> 16);
	buf[2] = (uint8_t)(val >> 8);
	buf[3] = (uint8_t)(val);
}

/* Helper: read uint32 big-endian from buffer */
static inline uint32_t ftp_get_u32(const uint8_t *buf)
{
	return ((uint32_t)buf[0] << 24) |
	   ((uint32_t)buf[1] << 16) |
	   ((uint32_t)buf[2] << 8)  |
	   ((uint32_t)buf[3]);
}

/* Helper: write uint64 big-endian into buffer */
static inline void ftp_put_u64(uint8_t *buf, uint64_t val)
{
	ftp_put_u32(buf, (uint32_t)(val >> 32));
	ftp_put_u32(buf + 4, (uint32_t)(val));
}

/* Helper: read uint64 big-endian from buffer */
static inline uint64_t ftp_get_u64(const uint8_t *buf)
{
	uint64_t hi = ftp_get_u32(buf);
	uint64_t lo;

	lo = ftp_get_u32(buf + 4);
	return (hi << 32) | lo;
}

#endif /* PROTOCOL_H */
