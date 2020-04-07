#ifndef BUTTON_H
#define BUTTON_H
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void InitializeButton(void);

uint8_t ButtonIsPressed(void);

#endif
