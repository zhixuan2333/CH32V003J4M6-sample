#include <debug.h>

void EXTI_INT_INIT(void)
{
  EXTI_InitTypeDef EXTI_InitStructure = {0};

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  EXTI_InitStructure.EXTI_Line = EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

int main(void)
{

  Delay_Init();   // Initialize delay function
  Delay_Ms(5000); // wait 5s for debugger connection
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  SystemCoreClockUpdate();

  EXTI_INT_INIT();

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Enable GPIOC clock
  GPIO_InitTypeDef GPIO_InitStructure = {0};
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;         // Pin 13
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // Push-pull output
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Speed 50
  GPIO_Init(GPIOC, &GPIO_InitStructure);            // Initialize GPIOC with the settings

  RCC_LSICmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    ;
  // LSI is 128kHz
  PWR_AWU_SetPrescaler(PWR_AWU_Prescaler_10240);
  PWR_AWU_SetWindowValue(10); // about x [ms]
  PWR_AutoWakeUpCmd(ENABLE);

  while (1)
  {

    GPIOC->OUTDR ^= GPIO_Pin_1; // Toggle the LED on/off
    // DLY_ms(500);                // wait 500ms
    Delay_Ms(100); // wait 100ms
    // __WFI();
    PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE);
  }
}
