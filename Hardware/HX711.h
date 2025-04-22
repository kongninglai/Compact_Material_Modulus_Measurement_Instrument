#ifndef __HX711_H
#define	__HX711_H
#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define		HX711_GPIO_CLK									RCC_APB2Periph_GPIOA
#define 	HX711_SCK_GPIO_PORT							GPIOA
#define 	HX711_SCK_GPIO_PIN							GPIO_Pin_0
#define 	HX711_DT_GPIO_PORT							GPIOA
#define 	HX711_DT_GPIO_PIN								GPIO_Pin_1
/*********************END**********************/

#define HX711_SCK_H				GPIO_SetBits(HX711_SCK_GPIO_PORT,HX711_SCK_GPIO_PIN);
#define HX711_SCK_L				GPIO_ResetBits(HX711_SCK_GPIO_PORT,HX711_SCK_GPIO_PIN);

#define HX711_DT					GPIO_ReadInputDataBit(HX711_DT_GPIO_PORT, HX711_DT_GPIO_PIN)

extern int HX711_Data_Reset;
extern volatile int HX711_Data_Real;
extern volatile uint8_t HX711_Data_Ready;

void HX711_Init(void);
void HX711_Reset(void);
unsigned long HX711_GetData(void);
#endif
