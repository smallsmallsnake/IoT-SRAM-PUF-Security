#include "./BSP/LED/led.h"

void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    LED0_GPIO_CLK_ENABLE();
    LED1_GPIO_CLK_ENABLE();

    gpio_init_struct.Pin   = LED0_GPIO_PIN;
    gpio_init_struct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin = LED1_GPIO_PIN;
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);

    LED0(1);
    LED1(1);
}
