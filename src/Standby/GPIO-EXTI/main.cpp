#include <debug.h>

void EXTI_INT_INIT(void)
{
    EXTI_InitTypeDef EXTI_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = EXTI7_0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


int main(void) {

  Delay_Init();            // Initialize delay function
  Delay_Ms(5000);        // wait 5s for debugger connection
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();

    EXTI_INT_INIT();

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Enable GPIOC clock
  GPIO_InitTypeDef GPIO_InitStructure = {0};
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // Pin 13
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Push-pull output
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Speed 50
  GPIO_Init(GPIOC, &GPIO_InitStructure); // Initialize GPIOC with the settings


  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure); // Initialize GPIOC with the settings


  // RCC_LSICmd(ENABLE);
  // while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
  // // LSI is 128kHz
  // PWR_AWU_SetPrescaler(PWR_AWU_Prescaler_10240);
  // PWR_AWU_SetWindowValue(10); // x [ms]
  // PWR_AutoWakeUpCmd(ENABLE);


  while(1) {

    GPIOC->OUTDR ^= GPIO_Pin_1; // Toggle the LED on/off
    Delay_Ms(100);                // wait 100ms
    PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE);

  }
}

