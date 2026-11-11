#ifndef SERVER_H
#define SERVER_H

/*
 * TCP server for file transport protocol.
 * Single-threaded, one client at a time.
 */

/*
 * Run the server on the given port. root_dir is the base directory for all file ops.
 * This function blocks until shutdown. Returns 0 on clean exit, -1 on error.
 */
int server_run(int port, const char *root_dir);

#endif /* SERVER_H */
