#ifndef TIMER_H
#define TIMER_H
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_tim.h>

void ConfigTimer2(uint32_t tau, uint32_t T);

void StartTimer2(void);
void StopTimer2(void);

extern void (*HighFunction)();
extern void (*LowFunction)();

#endif
