#include "stepper.h"

static uint8_t stepper_busy = 0;

void Stepper_Init(void)
{
    stepper_busy = 0;

    // Enable GPIO for direction pin
    RCC_APB2PeriphClockCmd(STEPPER_DIR_GPIO_RCC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = STEPPER_DIR_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(STEPPER_DIR_GPIO_PORT, &GPIO_InitStructure);

    Stepper_SetDirection(0); // Default direction: CW
}

void Stepper_SetDirection(uint8_t dir)
{
    if (dir == 0)
        GPIO_ResetBits(STEPPER_DIR_GPIO_PORT, STEPPER_DIR_GPIO_PIN); // CW
    else
        GPIO_SetBits(STEPPER_DIR_GPIO_PORT, STEPPER_DIR_GPIO_PIN);   // CCW
}

uint8_t Stepper_IsBusy(void)
{
    return stepper_busy;
}

static void TIM1_PWM_Config(uint32_t frequency_khz)
{
    uint32_t cycle = 1000 / frequency_khz;

    RCC_APB2PeriphClockCmd(STEPPER_PWM_GPIO_RCC | STEPPER_PWM_TIMER_RCC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = STEPPER_PWM_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = STEPPER_PWM_GPIO_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(STEPPER_PWM_GPIO_PORT, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = cycle - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(STEPPER_PWM_TIMER, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = cycle / 2;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    STEPPER_PWM_CHANNEL_INIT(STEPPER_PWM_TIMER, &TIM_OCInitStructure);

    TIM_SelectMasterSlaveMode(STEPPER_PWM_TIMER, TIM_MasterSlaveMode_Enable);
    TIM_SelectOutputTrigger(STEPPER_PWM_TIMER, TIM_TRGOSource_Update);

    STEPPER_PWM_OC_PRELOAD(STEPPER_PWM_TIMER, ENABLE);
    TIM_ARRPreloadConfig(STEPPER_PWM_TIMER, ENABLE);
}

static void TIM2_Counter_Config(uint32_t step_count)
{
    RCC_APB1PeriphClockCmd(STEPPER_COUNTER_TIMER_RCC, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = step_count;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(STEPPER_COUNTER_TIMER, &TIM_TimeBaseStructure);

    TIM_SelectInputTrigger(STEPPER_COUNTER_TIMER, TIM_TS_ITR0);
    STEPPER_COUNTER_TIMER->SMCR |= 0x07;

    TIM_ClearITPendingBit(STEPPER_COUNTER_TIMER, TIM_IT_Update);
    TIM_ITConfig(STEPPER_COUNTER_TIMER, TIM_IT_Update, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = STEPPER_COUNTER_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void Stepper_Run(uint32_t step_count, uint32_t frequency_khz)
{
    if (stepper_busy || frequency_khz == 0) return;
    stepper_busy = 1;

    uint32_t cycle = 1000 / frequency_khz;
    TIM2_Counter_Config(step_count);
    TIM1_PWM_Config(cycle);

    TIM_Cmd(STEPPER_COUNTER_TIMER, ENABLE);
    TIM_Cmd(STEPPER_PWM_TIMER, ENABLE);
    TIM_CtrlPWMOutputs(STEPPER_PWM_TIMER, ENABLE);
}


void Stepper_Run_Hz(uint32_t step_count, uint32_t frequency_hz)
{
    if (stepper_busy || frequency_hz == 0) return;
    stepper_busy = 1;

    uint32_t cycle = 1000000 / frequency_hz;  // base clock: 1 MHz
    TIM2_Counter_Config(step_count);
    TIM1_PWM_Config(cycle);

    TIM_Cmd(STEPPER_COUNTER_TIMER, ENABLE);
    TIM_Cmd(STEPPER_PWM_TIMER, ENABLE);
    TIM_CtrlPWMOutputs(STEPPER_PWM_TIMER, ENABLE);
}

void STEPPER_COUNTER_HANDLER(void)
{
    if (TIM_GetITStatus(STEPPER_COUNTER_TIMER, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(STEPPER_COUNTER_TIMER, TIM_IT_Update);
        TIM_CtrlPWMOutputs(STEPPER_PWM_TIMER, DISABLE);
        TIM_Cmd(STEPPER_PWM_TIMER, DISABLE);
        TIM_Cmd(STEPPER_COUNTER_TIMER, DISABLE);
        TIM_ITConfig(STEPPER_COUNTER_TIMER, TIM_IT_Update, DISABLE);
        stepper_busy = 0;
    }
}
