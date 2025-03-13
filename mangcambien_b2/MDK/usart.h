#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

void USART1_Init(void);
void UART1_Send_Char(char c);
void UART1_Send_String(char *str);
void UART1_Send_Number(int num);

#endif
