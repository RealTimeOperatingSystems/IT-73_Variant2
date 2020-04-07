#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "sysTickDelay.h"
#include "stepperMotor.h"
#include "button.h"

const uint32_t tau = 2;
const uint32_t T = 10;
const uint32_t neededPressedIterations = 100;

void turnOff(void);
void wait(void);
void turnOn(void);
void rotateClockwise(void);
void rotateCounterclockwise(void);

void (*currentStateFunc)() = wait;
void (*nextStateFunc)() = turnOn;

int main(void)
{
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
				currentStateFunc = nextStateFunc;
				currentPressedIterations = 0;
			}
		}
		else
		{
			currentPressedIterations = 0;
		}
		
		currentStateFunc();
		
		Delay(T - tau);
	}
}

void turnOff(void)
{
	TurnOffStepperMotor();
	currentStateFunc = wait;
	nextStateFunc = turnOn;
	Delay(tau);
}

void wait(void)
{
	Delay(tau);
}

void turnOn(void)
{
	TurnOnStepperMotor();
	currentStateFunc = rotateClockwise;
	nextStateFunc = rotateCounterclockwise;
	Delay(tau);
}

void rotateClockwise(void)
{
	StepperMotorSetDirection(Clockwise);
	StepperMotorMakeStep(tau);
	nextStateFunc = rotateCounterclockwise;
}

void rotateCounterclockwise(void)
{
	StepperMotorSetDirection(Counterclockwise);
	StepperMotorMakeStep(tau);
	nextStateFunc = turnOff;
}

void SysTick_Handler(void)
{
    SysTick_HandlerDelayFunc();
}
