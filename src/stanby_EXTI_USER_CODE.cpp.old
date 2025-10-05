#include <debug.h>

void EXTI_INT_INIT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};
  EXTI_InitTypeDef EXTI_InitStructure = {0};
  NVIC_InitTypeDef NVIC_InitStructure = {0};

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  // P2 as wake and reset pin
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure); // Initialize GPIOC with the settings

  // PC1 as LED pin
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;         // Pin 1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // Push-pull output
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Speed 50
  GPIO_Init(GPIOC, &GPIO_InitStructure);            // Initialize GPIOC with the settings

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);
  EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI7_0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

int main(void)
{

  Delay_Init();   // Initialize delay function
  Delay_Ms(5000); // wait 5s for debugger connection
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  SystemCoreClockUpdate();

  EXTI_INT_INIT();

  USART_Printf_Init(115200);
  printf("SystemClk:%d\r\n", SystemCoreClock);
  printf("PWR Standby Test\r\n");

  while (1)
  {

    GPIOC->OUTDR ^= GPIO_Pin_1; // Toggle the LED on/off
    Delay_Ms(1000);             // wait 100ms
    PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE);
    printf("Wake up from STANDBY mode\r\n");
  }
}

extern "C" {void EXTI7_0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));}

/*********************************************************************
 * @fn      EXTI0_IRQHandler
 *
 * @brief   This function handles EXTI0 Handler.
 *
 * @return  none
 */
void EXTI7_0_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    printf("EXTI Line2 Int Occur\r\n");
    GPIOC->OUTDR ^= GPIO_Pin_1;
    EXTI_ClearITPendingBit(EXTI_Line2); /* Clear Flag */
  }
}
