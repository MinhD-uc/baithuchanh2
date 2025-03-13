#include "test.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "usart.h"  
#include "delay.h"

void Timer2_Init(void) {
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
   
   TIM_TimeBaseInitTypeDef timerInit;
   timerInit.TIM_CounterMode = TIM_CounterMode_Up;
   timerInit.TIM_Period = 0xFFFF;
   timerInit.TIM_Prescaler = 72 - 1;
   TIM_TimeBaseInit(TIM2, &timerInit);
   TIM_Cmd(TIM2, ENABLE);

   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

   GPIO_InitTypeDef gpioInit;
   gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
   gpioInit.GPIO_Pin = GPIO_Pin_13;
   gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &gpioInit);

   gpioInit.GPIO_Mode = GPIO_Mode_Out_OD;
   gpioInit.GPIO_Pin = GPIO_Pin_12;
   gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &gpioInit);

   GPIO_ResetBits(GPIOB, GPIO_Pin_12);
   Delay_Ms(20);
   GPIO_SetBits(GPIOB, GPIO_Pin_12);

   uint16_t u16Tim;
   uint8_t u8Buff[5] = {0};
   uint8_t u8CheckSum = 0;

   TIM_SetCounter(TIM2, 0);
   while (TIM_GetCounter(TIM2) < 10) {
       if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) {
           break;
       }
   }
   u16Tim = TIM_GetCounter(TIM2);
   if (u16Tim >= 10) {
       while(1) {}
   }
TIM_SetCounter(TIM2, 0);
   while (TIM_GetCounter(TIM2) < 45) {
       if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) {
           break;
       }
   }
   u16Tim = TIM_GetCounter(TIM2);
   if ((u16Tim >= 45) || (u16Tim <= 5)) {
       while (1) {} 
   }

   TIM_SetCounter(TIM2, 0);
   while (TIM_GetCounter(TIM2) < 90) {
       if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) {
           break;
       }
   }
   u16Tim = TIM_GetCounter(TIM2);
   if ((u16Tim >= 90) || (u16Tim <= 70)) {
       while (1) {} 
   }

   TIM_SetCounter(TIM2, 0);
   while (TIM_GetCounter(TIM2) < 95) {
       if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) {
           break;
       }
   }
   u16Tim = TIM_GetCounter(TIM2);
   if ((u16Tim >= 95) || (u16Tim <= 75)) {
       while (1) {} 
   }

   for (int i = 0; i < 8; ++i) {
       TIM_SetCounter(TIM2, 0);
       while (TIM_GetCounter(TIM2) < 65) {
           if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) {
               break;
           }
       }
       u16Tim = TIM_GetCounter(TIM2);
       if ((u16Tim >= 65) || (u16Tim <= 45)) {
           while (1) {} 
       }

       TIM_SetCounter(TIM2, 0);
       while (TIM_GetCounter(TIM2) < 80) {
           if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) {
               break;
           }
       }
       u16Tim = TIM_GetCounter(TIM2);
       if ((u16Tim >= 80) || (u16Tim <= 10)) {
           while (1) {} 
       }

       u8Buff[0] <<= 1;
       if (u16Tim > 45) {
           u8Buff[0] |= 1;
       } else {
           u8Buff[0] &= ~1; 
       }
   }

   u8CheckSum = u8Buff[0] + u8Buff[1] + u8Buff[2] + u8Buff[3];
   if (u8CheckSum != u8Buff[4]) {
       while (1) {} 
   }

   UART1_Send_String("temperature: ");
   UART1_Send_Number(u8Buff[2]);
   UART1_Send_String("*C\n");
   UART1_Send_String("Humidity: ");
   UART1_Send_Number(u8Buff[0]);
   UART1_Send_String("%\n");
}
