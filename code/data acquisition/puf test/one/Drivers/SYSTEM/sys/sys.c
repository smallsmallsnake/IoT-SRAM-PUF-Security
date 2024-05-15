#include "./SYSTEM/sys/sys.h"

void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset)
{

    SCB->VTOR = baseaddr | (offset & (uint32_t)0xFFFFFE00);
}

void sys_wfi_set(void)
{
    __ASM volatile("wfi");
}

void sys_intx_disable(void)
{
    __ASM volatile("cpsid i");
}

void sys_intx_enable(void)
{
    __ASM volatile("cpsie i");
}

void sys_msr_msp(uint32_t addr)
{
    __set_MSP(addr);
}

void sys_standby(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();
    SET_BIT(PWR->CR, PWR_CR_PDDS);
}

void sys_soft_reset(void)
{
    NVIC_SystemReset();
}

uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp,
                             uint32_t pllq)
{
    HAL_StatusTypeDef ret           = HAL_OK;
    RCC_OscInitTypeDef rcc_osc_init = {0};
    RCC_ClkInitTypeDef rcc_clk_init = {0};

    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    rcc_osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    rcc_osc_init.HSEState       = RCC_HSE_ON;
    rcc_osc_init.PLL.PLLState   = RCC_PLL_ON;
    rcc_osc_init.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    rcc_osc_init.PLL.PLLN       = plln;
    rcc_osc_init.PLL.PLLM       = pllm;
    rcc_osc_init.PLL.PLLP       = pllp;
    rcc_osc_init.PLL.PLLQ       = pllq;
    ret                         = HAL_RCC_OscConfig(&rcc_osc_init);
    if (ret != HAL_OK) { return 1; }

    rcc_clk_init.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                              RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);

    rcc_clk_init.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    rcc_clk_init.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    rcc_clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
    rcc_clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
    ret = HAL_RCC_ClockConfig(&rcc_clk_init, FLASH_LATENCY_5);
    if (ret != HAL_OK) { return 1; }

    if (HAL_GetREVID() == 0x1001) { __HAL_FLASH_PREFETCH_BUFFER_ENABLE(); }
    return 0;
}