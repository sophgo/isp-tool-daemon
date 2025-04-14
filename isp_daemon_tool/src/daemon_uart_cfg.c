
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>

#include "daemon_base.h"
#include "daemon_uart_cfg.h"
#include "cvi_ispd2.h"

static int guart_fd = -1;
static struct termios goldtio = { 0 };
static int gconsole_recoverd;

static int get_console_tty(char *tty_name)
{
	char buffer[512];
	const char *command = "cat /proc/cmdline";
	FILE *fp = popen(command, "r");

	if (fp == NULL) {
		perror("popen");
		return 0;
	}
	fgets(buffer, sizeof(buffer), fp);
	pclose(fp);

	const char *needle = "console=";
	char *position = strstr(buffer, needle);

	if (position == NULL) {
		return 0;
	}

	strncpy(tty_name, "/dev/", 5 + 1);
	strncpy(tty_name + 5, position + sizeof(needle), 5);

	return 1;
}

static int release_uart_device(char *uart_device)
{
	int fd = fileno(stdin);
	char *current_tty = ttyname(fd);

	if (current_tty == NULL) {
		perror("Failed to get tty name");
		return 0;
	}

	char console_tty[12];

	memset(console_tty, 0, sizeof(console_tty));
	if (!get_console_tty(console_tty)) {
		return 0;
	}

	fd = open("/dev/tty1", O_RDONLY);
	if (fd < 0) {
		return 0;
	}
	if (strcmp(uart_device, current_tty) == 0) {
		ioctl(fd, TIOCCONS);
	} else if (strcmp("/dev/console", current_tty) == 0) {
		if (strcmp(uart_device, console_tty) == 0) {
			ioctl(fd, TIOCCONS);
		}
	} else if (strcmp(uart_device, console_tty) == 0) {
		ioctl(fd, TIOCCONS);
	}
	close(fd);
	return 1;
}

static void set_uart(int fd)
{
	struct termios newtio;

	tcgetattr(fd, &goldtio);
	tcgetattr(fd, &newtio);
	// bzero(&newtio, sizeof(newtio));

	cfsetospeed(&newtio, B115200);
	cfsetispeed(&newtio, B115200);

	newtio.c_cflag &= ~CSIZE;
	newtio.c_cflag |= HUPCL | CS8 | CLOCAL | CREAD;
	newtio.c_cflag &= ~PARENB;
	newtio.c_cflag &= ~CSTOPB;
	newtio.c_cflag &= ~CRTSCTS;

	newtio.c_iflag &= ~INPCK;
	newtio.c_iflag |= IGNPAR;
	newtio.c_iflag &= ~(IXON | IXOFF | IXANY);
	newtio.c_iflag &=
		~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

	newtio.c_oflag &= ~(ONLCR | OCRNL);
	newtio.c_oflag &= ~OPOST;
	newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG | IEXTEN);

	// newtio.c_cc[VTIME] = 0;
	// newtio.c_cc[VMIN] = 1;

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);
}

//-------------------------------------------------------------------------------------
void daemon_uart_console_recover(void)
{
	tcflush(guart_fd, TCIFLUSH);
	tcsetattr(guart_fd, TCSANOW, &goldtio);

	int fd = open("/dev/console", O_RDWR);

	ioctl(fd, TIOCCONS);
	close(fd);
	gconsole_recoverd = 1;
	clog_i("console recovered.\n");
}

//int daemon_uart_init(char *uart_name, int single_output)
int daemon_uart_init(char *uart_name)
{
	guart_fd = open(uart_name,
			O_RDWR | O_NOCTTY); // O_NOCTTY O_NDELAY O_NONBLOCK
	if (guart_fd < 0) {
		clog_e("open %s failed.\n", uart_name);
		return guart_fd;
	}

	if (!release_uart_device(uart_name)) {
		return -1;
	}

	set_uart(guart_fd);
	// fcntl(guart_fd, F_SETFL, 0); // FNDELAY
	isp_daemon2_uart_init(guart_fd);
	//isp_daemon2_enable_device_bind_control_uart(single_output ? 1 : 0);
	clog_i("started app in uart mode additionally, uart device:%s.\n",
	       uart_name);
	return guart_fd;
}

void daemon_uart_deinit(void)
{
	if (guart_fd >= 0) {
		isp_daemon2_uart_uninit();
		if (gconsole_recoverd == 0) {
			daemon_uart_console_recover();
		}
		close(guart_fd);
		guart_fd = -1;
	}
}
