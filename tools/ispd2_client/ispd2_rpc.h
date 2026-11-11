#ifndef _ISPD2_RPC_H_
#define _ISPD2_RPC_H_

#include <stddef.h>

#include "cvi_json_object.h"

/*
 * __printf(a, b) is a printf-format attribute hint. Defined by
 * linux/compiler.h; ispd2_rpc.c provides a local fallback if needed.
 */
#ifndef __printf
#define __printf(a, b)	__attribute__((__format__(__printf__, a, b)))
#endif

/* Error / status messages — always printed to console. */
#define ISPD2_CLI_PRT(fmt...) printf("[ispd2_cli] " fmt)

/*
 * Protocol-level logging (>> request / << response).
 *
 * Default: written to the log file opened with ispd2_open_log() (if any),
 * NOT printed to console.
 * With ispd2_set_verbose(1): also printed to console.
 */
void ispd2_rpc_log(const char *fmt, ...) __printf(1, 2);

/*
 * Open the protocol log file (truncate on open). Returns 0 on success, -1
 * on error. After this, >> / << messages are written here. Safe to call
 * with NULL path (no-op — messages dropped).
 */
int ispd2_open_log(const char *path);

/* Close the log file. Safe to call multiple times. */
void ispd2_close_log(void);

/*
 * Toggle console echo of >> / << messages. Default: off (file only).
 * Pass 1 to also print to console.
 */
void ispd2_set_verbose(int on);

/*
 * Connect to the isp daemon2 JSON-RPC server (blocking; 10s receive
 * timeout). Returns 0 on success, -1 on error.
 */
int ispd2_connect(const char *ip, int port);

void ispd2_close(void);

/*
 * Send one JSON-RPC 2.0 request:
 *   {"jsonrpc":"2.0","method":<method>,"id":<n>,"params":<params>}
 * params may be NULL. TAKES OWNERSHIP of params (the request object steals
 * the reference — bump with cvi_json_object_get() first if you keep it).
 * Returns the request id (>0), or -1 on error.
 */
int ispd2_send_request(const char *method, struct cvi_json_object *params);

/*
 * Receive one JSON-RPC reply. The daemon frames replies with NO delimiter:
 * complete JSON objects are emitted back-to-back, so the client accumulates
 * bytes and cuts a message on quote-aware {} / [] balance. Returns a NEW
 * cvi_json_object (caller cvi_json_object_put()s it) or NULL on
 * error / timeout / connection close.
 */
struct cvi_json_object *ispd2_recv_reply(void);

/*
 * Receive exactly n raw bytes (binary image / bin transfers). The daemon
 * sends the 4-byte ASCII sentinel "NONE" when it has no data. On success
 * *out receives a malloc'd buffer of n bytes (caller frees). Returns 0 on
 * success, 1 when the daemon answered "NONE" (*out stays NULL), -1 on
 * error.
 */
int ispd2_recv_binary(size_t n, unsigned char **out);

/* Send n raw bytes (import-bin phase 2). Returns 0 or -1. */
int ispd2_send_binary(const unsigned char *buf, size_t n);

#endif /* _ISPD2_RPC_H_ */
