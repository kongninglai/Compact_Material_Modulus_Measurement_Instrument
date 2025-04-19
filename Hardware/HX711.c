#include "HX711.h"
#include "Delay.h"


void HX711_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(HX711_GPIO_CLK , ENABLE);

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Pin = HX711_SCK_GPIO_PIN;
		GPIO_Init(HX711_SCK_GPIO_PORT, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = HX711_DT_GPIO_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   

		GPIO_Init(HX711_DT_GPIO_PORT, &GPIO_InitStructure);	

	
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

