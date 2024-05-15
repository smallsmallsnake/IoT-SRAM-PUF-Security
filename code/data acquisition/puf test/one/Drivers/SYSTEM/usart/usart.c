#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"

#if 1
#if (__ARMCC_VERSION >= 6010050)
__asm(".global __use_no_semihosting\n\t");
__asm(".global __ARM_use_no_argv \n\t");

#else

#pragma import(__use_no_semihosting)

struct __FILE {
    int handle;
};

#endif

int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

FILE __stdout;

int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0)
        ;

    USART1->DR = (uint8_t)ch;
    return ch;
}
#endif

void send1(uint8_t *buf, uint32_t len)
{
    HAL_UART_Transmit(&g_uart1_handle, buf, len, 0xFFFF);
}

#if USART_EN_RX

uint8_t g_usart_rx_buf[USART_REC_LEN];

uint16_t g_usart_rx_sta = 0;

uint8_t g_rx_buffer[RXBUFFERSIZE];

UART_HandleTypeDef g_uart1_handle;

void usart_init(uint32_t baudrate)
{
    g_uart1_handle.Instance        = USART_UX;
    g_uart1_handle.Init.BaudRate   = baudrate;
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;
    g_uart1_handle.Init.StopBits   = UART_STOPBITS_1;
    g_uart1_handle.Init.Parity     = UART_PARITY_NONE;
    g_uart1_handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    g_uart1_handle.Init.Mode       = UART_MODE_TX_RX;
    HAL_UART_Init(&g_uart1_handle);

    HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;
    if (huart->Instance == USART_UX) {
        USART_UX_CLK_ENABLE();
        USART_TX_GPIO_CLK_ENABLE();
        USART_RX_GPIO_CLK_ENABLE();

        gpio_init_struct.Pin       = USART_TX_GPIO_PIN;
        gpio_init_struct.Mode      = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull      = GPIO_PULLUP;
        gpio_init_struct.Speed     = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = USART_TX_GPIO_AF;
        HAL_GPIO_Init(USART_TX_GPIO_PORT, &gpio_init_struct);

        gpio_init_struct.Pin       = USART_RX_GPIO_PIN;
        gpio_init_struct.Alternate = USART_RX_GPIO_AF;
        HAL_GPIO_Init(USART_RX_GPIO_PORT, &gpio_init_struct);

#if USART_EN_RX
        HAL_NVIC_EnableIRQ(USART_UX_IRQn);
        HAL_NVIC_SetPriority(USART_UX_IRQn, 3, 3);
#endif
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART_UX) {
        g_usart_rx_buf[g_usart_rx_sta] = g_rx_buffer[0];
        g_usart_rx_sta += 1;
    }
}

void USART_UX_IRQHandler(void)
{
    uint32_t timeout  = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&g_uart1_handle);

    timeout = 0;
    while (HAL_UART_GetState(&g_uart1_handle) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout > maxDelay) { break; }
    }

    timeout = 0;

    while (HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer,
                               RXBUFFERSIZE) != HAL_OK) {
        timeout++;
        if (timeout > maxDelay) { break; }
    }
}

#endif
