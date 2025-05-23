#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*
uint8_t Key_Scan(uint16_t KEY_PORT){
	if (GPIO_ReadInputDataBit(GPIOA, KEY_PORT) == 1){
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA, KEY_PORT) == 1);
		Delay_ms(20);
		return 1;
	}
	return 0;
}*/

uint8_t Key_Scan(void)
{
	uint8_t KeyNum = 0;
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)			
	{
		delay_ms(20);											
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0);	
		delay_ms(20);											
		KeyNum = 1;												
	}
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)			
	{
		delay_ms(20);											
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0);	
		delay_ms(20);											
		KeyNum = 2;												
	}
	
	return KeyNum;			
}
