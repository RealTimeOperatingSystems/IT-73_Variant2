#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "sysTickDelay.h"

int main(void)
{	
	//initialization
	ConfigSysTickTimer();
	
	for(;;)
	{
		//loop work
		Delay(1000);
	}
}

void SysTick_Handler(void)
{
    SysTick_HandlerDelayFunc();
}
