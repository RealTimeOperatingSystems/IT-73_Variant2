#include "timer.h"

/* delay - greatest common divisor
 * delay = getGCD(tau, T);
 */
void ConfigTimer2(uint32_t tau, uint32_t T)
{
	// Init struct
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef timerPWM;
	
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// TIM_Period = 10 * delay - 1
	// Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * (TIM_Period + 1))
	// Update Event (Hz) = 72MHz / ((7199 + 1) * ((10 * 10 - 1) + 1)) = 100Hz (10ms)
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7199;
	TIM_TimeBaseInitStruct.TIM_Period = 10 * T - 1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	TIM_OCStructInit(&timerPWM);
	timerPWM.TIM_Pulse = 10 * tau;
  timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
  timerPWM.TIM_OutputState = TIM_OutputState_Enable;
  timerPWM.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM2, &timerPWM); // A2
}

void StartTimer2(void)
{
	TIM_Cmd(TIM2, ENABLE);
	TIM_SetCounter(TIM2, 0);
}

void StopTimer2(void)
{
	TIM_Cmd(TIM2, DISABLE);
}
