#ifndef _USART_H
#define _USART_H

#include "stdio.h"
#include "./SYSTEM/sys/sys.h"

#define USART_TX_GPIO_PORT GPIOA
#define USART_TX_GPIO_PIN  GPIO_PIN_9
#define USART_TX_GPIO_AF   GPIO_AF7_USART1
#define USART_TX_GPIO_CLK_ENABLE()                                             \
    do {                                                                       \
        __HAL_RCC_GPIOA_CLK_ENABLE();                                          \
    } while (0)

#define USART_RX_GPIO_PORT GPIOA
#define USART_RX_GPIO_PIN  GPIO_PIN_10
#define USART_RX_GPIO_AF   GPIO_AF7_USART1
#define USART_RX_GPIO_CLK_ENABLE()                                             \
    do {                                                                       \
        __HAL_RCC_GPIOA_CLK_ENABLE();                                          \
    } while (0)

#define USART_UX            USART1
#define USART_UX_IRQn       USART1_IRQn
#define USART_UX_IRQHandler USART1_IRQHandler
#define USART_UX_CLK_ENABLE()                                                  \
    do {                                                                       \
        __HAL_RCC_USART1_CLK_ENABLE();                                         \
    } while (0)

#define USART_REC_LEN 50
#define USART_EN_RX   1
#define RXBUFFERSIZE  1

extern UART_HandleTypeDef g_uart1_handle;

extern uint8_t g_usart_rx_buf[USART_REC_LEN];
extern uint16_t g_usart_rx_sta;
extern uint8_t g_rx_buffer[RXBUFFERSIZE];

void usart_init(uint32_t baudrate);

void send1(uint8_t *buf, uint32_t len);

#endif
