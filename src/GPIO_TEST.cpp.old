#include "debug.h"

void GPIO_Toggle_INIT(void)
{
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;

    GPIOC->CFGLR &= ~(0xF<<4);
    GPIOC->CFGLR |= (GPIO_Speed_10MHz | GPIO_Mode_Out_PP) << 4*1;

}

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();

    
    GPIO_Toggle_INIT();

    while(1)
    {
        Delay_Ms(250);
        GPIOC->OUTDR |= (1<<1);
        Delay_Ms(250);
        GPIOC->OUTDR &= ~(1<<1);
    }
}
