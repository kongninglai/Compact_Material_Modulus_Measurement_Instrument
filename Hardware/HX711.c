#include "HX711.h"
#include "Delay.h"

int HX711_Data_Reset;
// volatile uint8_t HX711_Data_Ready=0;

void HX711_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		// EXTI_InitTypeDef EXTI_InitStructure;
		// NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB2PeriphClockCmd(HX711_GPIO_CLK , ENABLE);

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Pin = HX711_SCK_GPIO_PIN;
		GPIO_Init(HX711_SCK_GPIO_PORT, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = HX711_DT_GPIO_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   

		GPIO_Init(HX711_DT_GPIO_PORT, &GPIO_InitStructure);	
		
		// GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
	
		// EXTI_InitStructure.EXTI_Line = EXTI_Line1;
		// EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		// EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		// EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		// EXTI_Init(&EXTI_InitStructure);
		
		// NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;
		// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
		// NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
		// NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		// NVIC_Init(&NVIC_InitStructure);
		
		//HX711_SCK_L;
}
	
unsigned long HX711_GetData(void)
{
		unsigned long Count;
		unsigned char i;
		HX711_SCK_L;
		delay_us(1);
		Count=0;
		while(HX711_DT);
		for (i=0;i<24;i++)
		{
				HX711_SCK_H;
				delay_us(1);
				Count=Count<<1;
				HX711_SCK_L;
				delay_us(1);
				if(HX711_DT) Count++;
		}
		HX711_SCK_H;
		delay_us(1);
		Count=Count^0x800000;
		HX711_SCK_L;
		delay_us(1);
		return(Count);
}

void HX711_Reset(void) {
	HX711_Data_Reset = HX711_GetData();
}

// void EXT1_IRQHandler(void) {
// 	if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
// 		EXTI_ClearITPendingBit(EXTI_Line1);
// 		HX711_Data_Ready = 1;
// 		HX711_Data_Real = HX711_GetData();
// 	}
// }
