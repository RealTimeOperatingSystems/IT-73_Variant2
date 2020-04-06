#include "sysTickDelay.h"

static __IO uint32_t TimingDelay;

void ConfigSysTickTimer(void)
{
	if (SysTick_Config(SystemCoreClock / 1000)) while (1);
}

void Delay(uint32_t milliseconds)
{ 
    TimingDelay = milliseconds;
    while(TimingDelay != 0);
}

void SysTick_HandlerDelayFunc(void)
{
    if (TimingDelay != 0x00) TimingDelay--;
}
