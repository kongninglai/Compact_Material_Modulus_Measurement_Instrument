#include "stm32f10x.h"                  // Device header

void PWM_Tim3Init(unsigned int pres,unsigned int period) 
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
  NVIC_InitTypeDef NVIC_InitTypeStruct;
  // TIM_OCInitTypeDef   TIM_OCInitTypeStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
  
  TIM_TimeBaseInitTypeStruct.TIM_Prescaler=pres;
  TIM_TimeBaseInitTypeStruct.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInitTypeStruct.TIM_Period=period;
  TIM_TimeBaseInitTypeStruct.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitTypeStruct);
  
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
  
  NVIC_InitTypeStruct.NVIC_IRQChannel=TIM3_IRQn;
  NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority=2;
  NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority=2;
  NVIC_InitTypeStruct.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitTypeStruct);
    
  TIM_SelectInputTrigger(TIM3,TIM_TS_ITR3);
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_External1);
  TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);
  TIM3->CNT=0X00;
  TIM_Cmd(TIM3,ENABLE);
  
}

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		//PB6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM4);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	
	// TIM_Cmd(TIM4, ENABLE);
	
	TIM_SelectOutputTrigger(TIM4,TIM_TRGOSource_OC1Ref); 
	TIM_SelectMasterSlaveMode(TIM4,TIM_MasterSlaveMode_Enable);
}

void TIM3_IRQHandler(void)   
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  
  {
    TIM_SetCompare1(TIM4,0);
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
  }
}

void PWM_SetCompare1(uint16_t Compare){
	TIM_SetCompare1(TIM4, Compare);
}

void PWM_Start(void){
	TIM_SetCompare1(TIM4, 50);
}

void PWM_Stop(void){
	TIM_SetCompare1(TIM4, 0);
}

void PWM_Steps(unsigned int steps) {
	PWM_Tim3Init(0,steps);
}
