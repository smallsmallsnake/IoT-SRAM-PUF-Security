#ifndef __LED_H
#define __LED_H

#include "./SYSTEM/sys/sys.h"

#define LED0_GPIO_PORT GPIOF
#define LED0_GPIO_PIN  GPIO_PIN_9
#define LED0_GPIO_CLK_ENABLE()                                                 \
    do {                                                                       \
        __HAL_RCC_GPIOF_CLK_ENABLE();                                          \
    } while (0)

#define LED1_GPIO_PORT GPIOF
#define LED1_GPIO_PIN  GPIO_PIN_10
#define LED1_GPIO_CLK_ENABLE()                                                 \
    do {                                                                       \
        __HAL_RCC_GPIOF_CLK_ENABLE();                                          \
    } while (0)

#define LED0(x)                                                                \
    do {                                                                       \
        x ? HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_SET)     \
          : HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_RESET);  \
    } while (0)

#define LED1(x)                                                                \
    do {                                                                       \
        x ? HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_SET)     \
          : HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_RESET);  \
    } while (0)

#define LED0_TOGGLE()                                                          \
    do {                                                                       \
        HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN);                     \
    } while (0)
#define LED1_TOGGLE()                                                          \
    do {                                                                       \
        HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_GPIO_PIN);                     \
    } while (0)

void led_init(void);

#endif // __LED_H
