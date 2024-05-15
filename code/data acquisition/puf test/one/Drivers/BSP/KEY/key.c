#include "./BSP/KEY/key.h"
#include "./SYSTEM/delay/delay.h"

void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    KEY0_GPIO_CLK_ENABLE();
    KEY1_GPIO_CLK_ENABLE();
    KEY2_GPIO_CLK_ENABLE();
    WKUP_GPIO_CLK_ENABLE();

    gpio_init_struct.Pin   = KEY0_GPIO_PIN;
    gpio_init_struct.Mode  = GPIO_MODE_INPUT;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KEY0_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin   = KEY1_GPIO_PIN;
    gpio_init_struct.Mode  = GPIO_MODE_INPUT;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KEY1_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin   = KEY2_GPIO_PIN;
    gpio_init_struct.Mode  = GPIO_MODE_INPUT;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KEY2_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.Pin   = WKUP_GPIO_PIN;
    gpio_init_struct.Mode  = GPIO_MODE_INPUT;
    gpio_init_struct.Pull  = GPIO_PULLDOWN;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(WKUP_GPIO_PORT, &gpio_init_struct);
}

uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;
    uint8_t keyval        = 0;

    if (mode) key_up = 1;

    if (key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1)) {
        delay_ms(10);
        key_up = 0;

        if (KEY0 == 0) keyval = KEY0_PRES;

        if (KEY1 == 0) keyval = KEY1_PRES;

        if (KEY2 == 0) keyval = KEY2_PRES;

        if (WK_UP == 1) keyval = WKUP_PRES;
    } else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0) {
        key_up = 1;
    }

    return keyval;
}
