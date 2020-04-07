#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "sysTickDelay.h"
#include "stepperMotor.h"
#include "button.h"

const uint32_t tau = 2;
const uint32_t T = 10;
const uint32_t neededPressedIterations = 100;

typedef enum
{
	TurningOff,
	TurnedOff,
	TurningOn,
	RotatingClockwise,
	RotatingCounterclockwise
} State;

int main(void)
{
	State currentState = TurnedOff;
	State nextState = TurningOn;
	uint32_t currentPressedIterations = 0;
	
	InitializeStepperMotor();
	
	ConfigSysTickTimer();
	
	TurnOnStepperMotor();
	
	for(;;)
	{
		//for slow state changing
		if(ButtonIsPressed())
		{
			currentPressedIterations++;
			if(currentPressedIterations >= neededPressedIterations)
			{
				currentState = nextState;
				currentPressedIterations = 0;
			}
		}
		else
		{
			currentPressedIterations = 0;
		}
		
		switch(currentState)
		{
			case TurningOff:
				TurnOffStepperMotor();
				currentState = TurnedOff;
				nextState = TurningOn;
				Delay(tau);
				break;
			
			case TurnedOff:
				Delay(tau);
				break;
			
			case TurningOn:
				TurnOnStepperMotor();
				currentState = RotatingClockwise;
				nextState = RotatingCounterclockwise;
				Delay(tau);
				break;
			
			case RotatingClockwise:
				StepperMotorSetDirection(Clockwise);
				StepperMotorMakeStep(tau);
				nextState = RotatingCounterclockwise;
				break;
			
			case RotatingCounterclockwise:
				StepperMotorSetDirection(Counterclockwise);
				StepperMotorMakeStep(tau);
				nextState = TurningOff;
				break;
		}
		
		Delay(T - tau);
	}
}

void SysTick_Handler(void)
{
    SysTick_HandlerDelayFunc();
}
