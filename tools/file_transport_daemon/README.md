# File Transport Daemon

A lightweight TCP file transport daemon for embedded Linux systems. Serves files over a simple binary protocol to a client (pqtool UI).

## Features

- Pure C11, no external dependencies (only libc, POSIX)
- Single-threaded, uses select() for I/O multiplexing
- Memory usage < 1MB for normal operations
- Path traversal protection (rejects "..", validates against root_dir)
- Symlink escape prevention via realpath()
- Handles one client at a time (embedded resource constraint)

## Build

### Native build

```bash
make
```

### Cross-compile

```bash
make CC=arm-linux-gnueabihf-gcc
```

### Install

```bash
sudo make install
```

This copies the binary to `/usr/local/bin/file_transport_daemon`.

## Usage

```bash
./file_transport_daemon [-p port] [-r root_dir]
```

| Option | Description | Default |
|--------|-------------|---------|
| `-p`   | TCP port to listen on | 6677 |
| `-r`   | Base directory for file operations (all paths relative to this) | `$HOME` (fallback: `/mnt/`, `/data/`, `/`) |

Default root resolution order:
1. `$HOME` — most useful for dev machines
2. `/mnt/` — common on embedded devices
3. `/data/` — common on devices with separate storage partition
4. `/` — last resort

Examples:

```bash
# Serve files from /data with default port
./file_transport_daemon -r /data

# Use custom port and root
./file_transport_daemon -p 8080 -r /home/user/files
```

## Protocol Summary

All integers are **big-endian** (network byte order).

### Header (16 bytes)

| Field | Size | Description |
|-------|------|-------------|
| magic | 4 bytes | `F`, `T`, `P`, `T` (0x46, 0x54, 0x50, 0x54) |
| cmd | uint32 | Command code |
| seq | uint32 | Sequence number |
| payload_len | uint32 | Length of following payload |

### Commands

| Code | Name | Direction | Description |
|------|------|-----------|-------------|
| 0x01 | LIST_REQ | Client→Server | List directory |
| 0x02 | LIST_RSP | Server→Client | Directory listing |
| 0x03 | DOWNLOAD_REQ | Client→Server | Request file download |
| 0x04 | DOWNLOAD_CHUNK | Server→Client | File data chunk |
| 0x05 | DOWNLOAD_DONE | Server→Client | Download finished |
| 0x06 | UPLOAD_REQ | Client→Server | Initiate upload |
| 0x07 | UPLOAD_CHUNK | Client→Server | File data chunk |
| 0x08 | UPLOAD_DONE | Client→Server | Upload finished |
| 0x09 | MKDIR_REQ | Client→Server | Create directory |
| 0x0A | DELETE_REQ | Client→Server | Delete file/directory |
| 0x0B | QUERY_ROOT_REQ | Client→Server | Query daemon's root directory |
| 0x0C | QUERY_ROOT_RSP | Server→Client | Root directory path (UTF-8) |
| 0x10 | ACK | Server→Client | Generic success |
| 0x11 | ERROR_RSP | Server→Client | Error response |

### Payload Formats

- **LIST_REQ**: path (UTF-8, not null-terminated)
- **LIST_RSP**: repeated entries: name_len(u32) + name + flags(u8) + size(u64) + mtime(u64)
- **DOWNLOAD_REQ**: path (UTF-8)
- **DOWNLOAD_CHUNK**: offset(u64) + data bytes
- **DOWNLOAD_DONE**: file_size(u64)
- **UPLOAD_REQ**: file_size(u64) + path (UTF-8)
- **UPLOAD_CHUNK**: offset(u64) + data bytes
- **UPLOAD_DONE**: empty
- **MKDIR_REQ**: path (UTF-8)
- **DELETE_REQ**: path (UTF-8)
- **QUERY_ROOT_REQ**: empty
- **QUERY_ROOT_RSP**: root_path (UTF-8, not null-terminated)
- **ACK**: original_cmd(u32)
- **ERROR_RSP**: original_cmd(u32) + error_code(u32) + error_msg(UTF-8)

### Error Codes

| Code | Meaning |
|------|---------|
| 1 | ENOENT (file not found) |
| 2 | EACCES (permission denied) |
| 3 | EIO (I/O error) |
| 4 | EINVAL (invalid argument) |
| 5 | ENOMEM (out of memory) |

### Chunk Size

File transfers use 64KB (65536 bytes) chunks.

## Security

- All client paths are relative to the configured root_dir
- Paths containing `..` are rejected
- Absolute paths from client are rejected
- Symlinks that escape root_dir are blocked via realpath()
- Payload size capped at 16MB to prevent memory exhaustion
