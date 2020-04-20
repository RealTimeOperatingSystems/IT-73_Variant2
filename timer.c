#include "timer.h"

/* Greatest common divisor: Euclidean algorithm
 * getGCD(2, 10) = 2;
 * getGCD(2, 17) = 1;
 * getGCD(4, 14) = 2;
 */
uint32_t getGCD(uint32_t a, uint32_t b)
{
	while (a != b)
	{
		if (a > b)
		{
			uint32_t tmp = a;
			a = b;
			b = tmp;
		}
		b = b - a;
	}
	return a;
}

static __IO uint32_t tauDelayCount;
static __IO uint32_t TDelayCount;
static __IO uint32_t currentDelayCount;

/* delay - greatest common divisor
 * delay = getGCD(tau, T);
 */
void ConfigTimer2(uint32_t tau, uint32_t T)
{
	// Init struct
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	uint32_t delay = getGCD(tau, T); //getGCD(2, 10) = 2;
	tauDelayCount = tau / delay; // 2 / 2 = 1
	TDelayCount = T / delay; // 10 / 2 = 5
	//[0]1|2|3|4 - high: [0], low: [1;4]
	// TIM_Period = 10 * delay - 1
	// Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * (TIM_Period + 1))
	// Update Event (Hz) = 72MHz / ((7199 + 1) * ((10 * 2 - 1) + 1)) = 500Hz (2ms)
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7199;
	TIM_TimeBaseInitStruct.TIM_Period = 10 * delay - 1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
		
	// Enable TIM2 interrupt
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// Nested vectored interrupt settings
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void StartTimer2(void)
{
	TIM_Cmd(TIM2, ENABLE);
	TIM_SetCounter(TIM2, 0);
	currentDelayCount = 0;
}

void StopTimer2(void)
{
	TIM_Cmd(TIM2, DISABLE);
}

void TIM2_IRQHandler(void)
{
	// Checks whether the TIM2 interrupt has occurred or not
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		if(currentDelayCount < tauDelayCount)
		{
			HighFunction();
		}
		else
		{
			LowFunction();
		}
		
		currentDelayCount++;
		
		if(currentDelayCount >= TDelayCount)
		{
			currentDelayCount = 0;
		}
		
		// Clears the TIM2 interrupt pending bit
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
