#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"
#include "Serial.h"
#include "HX711.h"
#include "PWM.h"
#include "Timer.h"

int value;

int reset;
u8 buff[30];

uint8_t RxData;
uint8_t Key_Pressed;
uint8_t PWM_Enabled;
#define KEY_DIR 0x1
#define KEY_ENA 0x2
uint8_t Timer_Triggered = 0;
int main(void)
{ 
	SystemInit();
	delay_init(72);
	Serial_Init();
	//Key_Init();
	LED_Init();
	HX711_Init();
	delay_ms(2000);
	reset = HX711_GetData();
	PWM_Init();
	Timer_Init();
	TIM_Cmd(TIM4,ENABLE);
	PWM_Enabled = 0;
	while (1)
	{
		value = HX711_GetData() - reset;
		Key_Pressed = Key_Scan();

		if (Key_Pressed == KEY_DIR){
			reset = HX711_GetData();
		}
		
		if (Timer_Triggered) {
			Timer_Triggered = 0;
			if (value >= 0){
				Serial_Printf("+%d\r\n", value);
			} else {
				Serial_Printf("-%d\r\n", -value);
			}
		}

		if (Serial_GetRxFlag() == 1)
 		{
			RxData = Serial_GetRxData();
			if (RxData == KEY_DIR){
				LED_DIR_Turn();
			}
			if (RxData == KEY_ENA){
				if (PWM_Enabled) {
					PWM_Enabled = 0;
					PWM_Stop();
				} else {
					PWM_Enabled = 1;
					PWM_Start();
				}
			}
		}
	}
}
