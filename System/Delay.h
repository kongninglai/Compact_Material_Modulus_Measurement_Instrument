// #ifndef __DELAY_H
// #define __DELAY_H

// void Delay_us(uint32_t us);
// void Delay_ms(uint32_t ms);
// void Delay_s(uint32_t s);

// #endif
#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif

