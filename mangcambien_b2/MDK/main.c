#include "test.h"
#include "usart.h"

int main(void) {
    USART1_Init();
    UART1_Send_String("Hello, USART!\n");
	  Timer2_Init();
    while (1) {
        
    }
		
}
