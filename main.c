#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "initialization.h"
#include "delay.h"

const int T = 20;
const int a1_t = 10;
const int b9_t = 5;

int main(void)
{	
	initialize();
	
	for(;;)
	{
		GPIOB->ODR |= GPIO_Pin_9;
		GPIOA->ODR |= GPIO_Pin_1;
		
		if(a1_t < b9_t)
		{
			delay(a1_t);
			GPIOA->ODR &= ~GPIO_Pin_1;
			
			delay(b9_t - a1_t);
			GPIOB->ODR &= ~GPIO_Pin_9;
		
			delay(T - b9_t);
		}
		else
		{
			delay(b9_t);
			GPIOB->ODR &= ~GPIO_Pin_9;
			
			delay(a1_t - b9_t);
			GPIOA->ODR &= ~GPIO_Pin_1;
		
			delay(T - a1_t);
		}
	}
}
