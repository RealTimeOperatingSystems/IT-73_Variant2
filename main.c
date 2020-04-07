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

State currentState = TurnedOff;
State nextState = TurningOn;

void turnOff(void);
void wait(void);
void turnOn(void);
void rotateClockwise(void);
void rotateCounterclockwise(void);

void (*funcArray[])() = {turnOff, wait, turnOn, rotateClockwise, rotateCounterclockwise};

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
				currentState = nextState;
				currentPressedIterations = 0;
			}
		}
		else
		{
			currentPressedIterations = 0;
		}
		
		funcArray[currentState]();
		
		Delay(T - tau);
	}
}

void turnOff(void)
{
	TurnOffStepperMotor();
	currentState = TurnedOff;
	nextState = TurningOn;
	Delay(tau);
}

void wait(void)
{
	Delay(tau);
}

void turnOn(void)
{
	TurnOnStepperMotor();
	currentState = RotatingClockwise;
	nextState = RotatingCounterclockwise;
	Delay(tau);
}

void rotateClockwise(void)
{
	StepperMotorSetDirection(Clockwise);
	StepperMotorMakeStep(tau);
	nextState = RotatingCounterclockwise;
}

void rotateCounterclockwise(void)
{
	StepperMotorSetDirection(Counterclockwise);
	StepperMotorMakeStep(tau);
	nextState = TurningOff;
}

void SysTick_Handler(void)
{
    SysTick_HandlerDelayFunc();
}
