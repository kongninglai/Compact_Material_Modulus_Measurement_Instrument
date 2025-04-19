// #include "stm32f10x.h"                  // Device header
// #include "Delay.h"
// #include "OLED.h"
// #include "PWM.h"
// #include "Key.h"
// #include "LED.h"
// #include "Serial.h"
// #include "HX711.h"

// uint8_t RxData;
// uint8_t PWM_Enabled;
// uint8_t Key_Pressed;
// #define KEY_DIR 0x1
// #define KEY_ENA 0x2
// //uint32_t data=0;
// int main(void)
// {
// 	SystemInit();
// 	OLED_Init();
// 	Init_HX711pin();
// 	//PWM_Init();
// 	//Serial_Init();
// 	//Key_Init();
// 	//LED_Init();
// 	//PWM_Enabled = 0;
// 	//LED_DIR_ON();
// 	//PWM_SetCompare1(50);
// 	Get_Maopi();
// 	//OLED_ShowString(3, 1, "Maopi:");
// 	Delay_ms(1000);
// 	Get_Maopi();
// 	OLED_ShowNum(4, 1, Weight_Maopi, 10);
// 	uint8_t i = 0;
// 	uint32_t result = 0;
// 	while (1)
// 	{	
		
// 		/*Key_Pressed = Key_Scan();
// 		if (Key_Pressed == KEY_DIR){
// 			Get_Maopi();
// 		}*/
// 		result = 0;
// 		for (i = 0; i < 3; i++){
// 			Get_Weight();
// 			result = result + Weight_Shiwu;
// 		}
// 		result = result / 3;
// 		//Get_Weight();
// 		//Serial_Printf("DATA = %d                                          ", HX711_Buffer);
// 		OLED_ShowString(1, 1, "DATA:");
// 		//OLED_ShowNum(2, 1, HX711_DATA_READ(), 10);
// 		OLED_ShowNum(2, 1, result, 10);
		
// 		Delay_ms(500);
// 		/*
// 		if (Serial_GetRxFlag() == 1)
// 		{
// 			//OLED_ShowString(2, 1, "Hello!");
// 			RxData = Serial_GetRxData();
// 			if (RxData == KEY_DIR){
// 				LED_DIR_Turn();
// 				OLED_ShowString(3, 1, "DIR");
// 			}
// 			if (RxData == KEY_ENA){
// 				OLED_ShowString(3, 1, "ENA");
// 				if (PWM_Enabled){
// 					PWM_SetCompare1(0);
// 					PWM_Enabled = 0;
// 				}else{
// 					PWM_SetCompare1(50);
// 					PWM_Enabled = 1;
// 				}
// 			}
// 		}*/
		
// 		/*
// 		Key_Pressed = Key_Scan();
// 		if (Key_Pressed == KEY_DIR){
// 			LED_DIR_Turn();
// 		}
// 		if (Key_Pressed == KEY_ENA){
// 			if (PWM_Enabled){
// 				PWM_SetCompare1(0);
// 				PWM_Enabled = 0;
// 			}else{
// 				PWM_SetCompare1(50);
// 				PWM_Enabled = 1;
// 			}
// 		}
// 		*/
// 	}
// }
