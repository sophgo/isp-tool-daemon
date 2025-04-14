
#ifndef __DAEMON_UART_CFG_H__
#define __DAEMON_UART_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif

int daemon_uart_init(char *uart_name);
void daemon_uart_deinit(void);
void daemon_uart_console_recover(void);

#ifdef __cplusplus
}
#endif
#endif
