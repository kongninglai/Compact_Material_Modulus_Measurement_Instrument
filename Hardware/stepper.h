#ifndef __STEPPER_H
#define __STEPPER_H

#include "stm32f10x.h"

// === GPIO & TIMER Macros === //
#define STEPPER_PWM_GPIO_RCC     RCC_APB2Periph_GPIOA
#define STEPPER_PWM_GPIO_PORT    GPIOA
#define STEPPER_PWM_GPIO_PIN     GPIO_Pin_8  // TIM1_CH1
#define STEPPER_PWM_GPIO_AF      GPIO_Mode_AF_PP

#define STEPPER_PWM_TIMER_RCC    RCC_APB2Periph_TIM1
#define STEPPER_PWM_TIMER        TIM1
#define STEPPER_PWM_CHANNEL_INIT TIM_OC1Init
#define STEPPER_PWM_OC_PRELOAD   TIM_OC1PreloadConfig

#define STEPPER_COUNTER_TIMER_RCC  RCC_APB1Periph_TIM2
#define STEPPER_COUNTER_TIMER      TIM2
#define STEPPER_COUNTER_IRQ        TIM2_IRQn
#define STEPPER_COUNTER_HANDLER    TIM2_IRQHandler

// === Direction Control (PB5) === //
#define STEPPER_DIR_GPIO_RCC     RCC_APB2Periph_GPIOB
#define STEPPER_DIR_GPIO_PORT    GPIOB
#define STEPPER_DIR_GPIO_PIN     GPIO_Pin_5

// === Public API === //
void Stepper_Init(void);
void Stepper_Run(uint32_t step_count, uint32_t frequency_khz);
void Stepper_Run_Hz(uint32_t step_count, uint32_t frequency_hz);
void Stepper_SetDirection(uint8_t dir); // 0: CW, 1: CCW
uint8_t Stepper_IsBusy(void);

#endif
