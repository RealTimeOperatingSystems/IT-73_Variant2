#ifndef SYSTICKDELAY_H
#define SYSTICKDELAY_H
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void ConfigSysTickTimer(void);
void Delay(uint32_t milliseconds);
void SysTick_HandlerDelayFunc(void);

#endif
