#include "debug.h"

void GPIO_Toggle_INIT(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();

    
    GPIO_Toggle_INIT();

    while(1)
    {
        if((GPIOC->INDR & GPIO_Pin_2) == 0x00)
        // is GND
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
        else
        // is VCC
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
        Delay_Ms(250);
    }
}
