#include <string.h>

#include <SYSTEM/sys/sys.h>
#include <SYSTEM/usart/usart.h>
#include <SYSTEM/delay/delay.h>
#include <BSP/LED/led.h>
#include <BSP/KEY/key.h>

#include <SYSTEM/bch/bch.h>
#include <SYSTEM/aes/aes.h>
#include "timer.h" 

#define OC_SRAM_1_BASE_ADDR 0x20000000 
#define OC_SRAM_2_BASE_ADDR 0x10000000 //Only this address is currently used

void oc_sram_read(uint8_t *buf, uint32_t addr, uint32_t len, uint8_t cs)
{
    int base_addr;
    if (cs == 1) {
        base_addr = OC_SRAM_1_BASE_ADDR;
    } else if (cs == 2) {
        base_addr = OC_SRAM_2_BASE_ADDR;
    }

    for (; len > 0; len--) {
        *buf++ = *(uint8_t *)(base_addr + addr);
        addr++;
    }
}




void sram_test1()//Test SRAM2 read operation
{
    uint8_t temp[8];

   
    for (uint32_t addr = 0; addr < 64 * 1024; addr += 8) {
        oc_sram_read(temp, addr, 8, 2);
        send1(temp, 8);   }
   
}


void sram_test11()//Test SRAM2 read operation and test time
{
    uint8_t temp[8],t=0;
    uint32_t  Counter=0,Time;
    
    
    for (uint32_t addr = 0; addr < 64 * 1024; addr += 8) {
        
        if(t==0)
        {
            Tcnt=0;
            __HAL_TIM_SET_COUNTER(&TIM3_Handler,0);	
           
        }
        oc_sram_read(temp, addr, 8, 2);
        
        send1(temp, 8);
        t++;
        
        if(t==10)
        {     Counter = __HAL_TIM_GET_COUNTER(&TIM3_Handler); 
            Time=Tcnt*5000+Counter;
            printf("\r\nTime:%d us  ***********************\r\n",Time);
            t=0;
        }
    }
    
} 

uint32_t array2int(const uint8_t *array)
{
    uint32_t result = 0;
    int a           = 0;
    for (int i = 0; i < 4; i++) {
        a = array[i];
        result += a << (8 * (3 - i));
    }
    return result;
}


int main(void)
{
    uint8_t key = 0;

    HAL_Init();                     
    sys_stm32_clock_init(336, 8, 2, 7); 
    delay_init(168);                   
    usart_init(115200);               
    led_init();               
    key_init();                    

     TIM3_Init(5000-1,84-1);     //5000us

    
    while (1) {
        key = key_scan(0);
        if (key == KEY0_PRES) {
           
            sram_test1();
        } else if (key == KEY1_PRES) {
            sram_test11();
            
        } else if (key == KEY2_PRES) {
           
        }
    }
}
