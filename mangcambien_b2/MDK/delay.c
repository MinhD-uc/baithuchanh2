#include "stm32f10x.h"

void Delay_Ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 4000; i++) {
        __NOP(); 
    }
}
