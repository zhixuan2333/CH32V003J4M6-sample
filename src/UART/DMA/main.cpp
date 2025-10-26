#include "debug.h"

// This example demonstrates USART1 communication using DMA loop mode to continuously
// send and receive data. The transmitted data is toggled each cycle, and the received
// data is displayed on a GPIO pin (GPIOD.0) bit by bit.

/* Global define */
#define TxSize1 1
#define size(a) (sizeof(a) / sizeof(*(a)))

/* Global Variable */
u8 TxBuffer1 = 0b01000010;
u8 RxBuffer1 = 0;

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIOA.0
 *
 * @return  none
 */
void GPIO_Toggle_INIT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART1peripheral.
 *
 * @return  none
 */
void USARTx_CFG(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};
  USART_InitTypeDef USART_InitStructure = {0};

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

  /* USART1 TX-->D.5   RX-->D.6 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

  USART_Init(USART1, &USART_InitStructure);

  DMA_Cmd(DMA1_Channel4, ENABLE); /* USART1 Tx */
  DMA_Cmd(DMA1_Channel5, ENABLE); /* USART1 Rx */

  USART_Cmd(USART1, ENABLE);
}

/*********************************************************************
 * @fn      DMA_INIT
 *
 * @brief   Configures the DMA for USART1.
 *
 * @return  none
 */
void DMA_INIT(void)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  DMA_InitTypeDef DMA_InitStructure = {0};
  DMA_DeInit(DMA1_Channel4);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DATAR);
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&TxBuffer1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = TxSize1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);

  DMA_DeInit(DMA1_Channel5);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DATAR);
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&RxBuffer1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = TxSize1;
  DMA_Init(DMA1_Channel5, &DMA_InitStructure);
  // Enable loop mode
  DMA1_Channel5->CFGR |= (0b1 << 5);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  SystemCoreClockUpdate();
  Delay_Init();
  GPIO_Toggle_INIT();
  DMA_INIT();
  USARTx_CFG(); /* USART1 */
  USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
  Delay_Ms(1000);
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

  while (1)
  {
    DMA_Cmd(DMA1_Channel5, ENABLE);

    for (uint8_t i = 0; i < 8; i++)
    {
      GPIO_WriteBit(GPIOD, GPIO_Pin_0, (RxBuffer1 & (1 << i)) ? Bit_SET : Bit_RESET);
      Delay_Us(5);
    }

    // Reload DMA for next transfer Tx
    DMA1_Channel4->CNTR = TxSize1;
    DMA_Cmd(DMA1_Channel4, ENABLE);

    TxBuffer1 = ~TxBuffer1;
    Delay_Ms(500);

    while (DMA_GetFlagStatus(DMA1_FLAG_TC4) == RESET) /* Wait until USART1 TX DMA1 Transfer Complete */
    {
    }
    while (DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET) /* Wait until USART1 RX DMA1 Transfer Complete */
    {
    }
  }
}
