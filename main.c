#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "sysTickDelay.h"
#include "stepperMotor.h"

const uint32_t tau = 2;
const uint32_t T = 10;

int main(void)
{
	InitializeStepperMotor();
	
	ConfigSysTickTimer();
	
	TurnOnStepperMotor();
	
	for(;;)
	{
		StepperMotorMakeStep(tau);
		Delay(T - tau);
	}
}

void SysTick_Handler(void)
{
    SysTick_HandlerDelayFunc();
}
