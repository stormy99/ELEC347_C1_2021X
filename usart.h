#ifndef _USART_H_
#define _USART_H_

#define USART_MODULE  USART3
#define USART_PORT  GPIOD
#define USART_TX_pin  8
#define USART_RX_pin  9
#define BAUDRATE  115200

void init_usart(void);
void send_usart_str(char *str);
void send_usart_char(char d);
void clear_usart(void);

#endif
