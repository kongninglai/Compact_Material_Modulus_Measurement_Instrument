#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "stepper.h"
#include "Key.h"
#include "LED.h"
#include "Serial.h"
#include "HX711.h"

int value;
float weight;
int32_t reset;
u8 buff[30];

float Weights=100.0;  //100g
int32_t Weights_100=8493860;  //100g

int main(void)
{ 
	Stepper_Init();

	// 200 steps, 10kHZ
	Stepper_SetDirection(0);
	Stepper_Run(200, 10);

	// wait for finishing
	while (Stepper_IsBusy());

	// 400 steps, 100HZ
	Stepper_SetDirection(1);
	Stepper_Run_Hz(400, 100);

	// SystemInit();
	// delay_init(72);
	// HX711_Init();
	
	// OLED_Init();
	// delay_ms(2000);
	
	// reset = HX711_GetData();
	// OLED_ShowString(1, 1, "DATA:");
	// OLED_ShowHexNum(3,1,reset,10);
	// while (1)
	// {
	// 	value = HX711_GetData() - reset;
		
	// 	//weight=(float)(value-reset)*Weights/(float)(Weights_100-reset
	// 	if (value >= 0){
	// 		OLED_ShowString(2, 1, "+");
	// 		OLED_ShowHexNum(2,2,value,6);
	// 	} else {
	// 		OLED_ShowString(2, 1, "-");
	// 		OLED_ShowHexNum(2,2,-value,6);
	// 	}
		
	// 	//OLED_ShowNum(2,1,value,10);

	// 	delay_ms(500);
	// }
}
