#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "sysTickDelay.h"
#include "stepperMotor.h"
#include "button.h"
#include "timer.h"

const uint32_t tau = 2;
const uint32_t T = 10;
const uint32_t neededPressedIterations = 100;

typedef enum
{
	TurnedOff,
	TurnedOn,
	RotatingClockwise,
	RotatingCounterclockwise
} State;

State currentState = TurnedOff;
State nextState = TurnedOn;

void turnOff(void);
void wait(void);
void turnOn(void);
void rotateClockwise(void);
void rotateCounterclockwise(void);

void (*funcArray[])() = {turnOff, turnOn, rotateClockwise, rotateCounterclockwise};

void (*HighFunction)() = StepperMotorSetBits;
void (*LowFunction)() = StepperMotorResetBits;

int main(void)
{
	uint32_t currentPressedIterations = 0;
	
	InitializeStepperMotor();
	
	ConfigSysTickTimer();
	
	ConfigTimer2(tau, T);
	
	TurnOffStepperMotor();
	
	for(;;)
	{
		//for slow state changing
		if(ButtonIsPressed())
		{
			currentPressedIterations++;
			if(currentPressedIterations >= neededPressedIterations)
			{
				currentState = nextState;
				funcArray[currentState]();
				currentPressedIterations = 0;
			}
		}
		else
		{
			currentPressedIterations = 0;
		}
		
		Delay(T);
	}
}

void do_nothing(void)
{
	//do nothing
}

void turnOff(void)
{
	TurnOffStepperMotor();
	StopTimer2();
	nextState = TurnedOn;
}

void turnOn(void)
{
	TurnOnStepperMotor();
	StartTimer2();
	HighFunction = do_nothing;
	nextState = RotatingClockwise;
}

void rotateClockwise(void)
{
	StepperMotorSetDirection(Clockwise);
	HighFunction = StepperMotorSetBits;
	nextState = RotatingCounterclockwise;
}

void rotateCounterclockwise(void)
{
	StepperMotorSetDirection(Counterclockwise);
	HighFunction = StepperMotorSetBits;
	nextState = TurnedOff;
}

void SysTick_Handler(void)
{
    SysTick_HandlerDelayFunc();
}
