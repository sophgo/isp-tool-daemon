#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include "server.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

/* Defined in server.c */
extern void server_set_running(int val);

static void signal_handler(int sig)
{
	(void)sig;
	server_set_running(0);
}

static void print_usage(const char *prog)
{
	fprintf(stderr, "Usage: %s [-p port] [-r root_dir]\n", prog);
	fprintf(stderr, "  -p port      TCP port to listen on (default: 6677)\n");
	fprintf(stderr,
		"  -r root_dir  Restrict access to this directory (optional)\n");
	fprintf(stderr,
		"               Without -r, the daemon allows access to any path.\n");
}

int main(int argc, char *argv[])
{
	int port = 6677;
	const char *root_dir = NULL;
	int opt;
	struct sigaction sa;
	int ret;

	while ((opt = getopt(argc, argv, "p:r:h")) != -1) {
		switch (opt) {
		case 'p':
			port = atoi(optarg);
			if (port <= 0 || port > 65535) {
				fprintf(stderr, "Invalid port: %s\n", optarg);
				return 1;
			}
			break;
		case 'r':
			root_dir = optarg;
			break;
		case 'h':
			print_usage(argv[0]);
			return 0;
		default:
			print_usage(argv[0]);
			return 1;
		}
	}

	/* Install signal handlers */
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);

	/* Ignore SIGPIPE to avoid crashes on broken connections */
	signal(SIGPIPE, SIG_IGN);

	printf("File Transport Daemon starting...\n");
	printf("  Port: %d\n", port);
	if (root_dir)
		printf("  Root: %s (access restricted)\n", root_dir);
	else
		printf("  Root: (none - unrestricted access)\n");

	ret = server_run(port, root_dir);

	printf("File Transport Daemon exiting (code %d)\n", ret);
	return ret == 0 ? 0 : 1;
}
