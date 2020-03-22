#include "initialization.h"
#include "stm32f10x.h"

void set_port_a1_as_output(void)
{
	GPIOA->CRL |= GPIO_CRL_MODE1;
	GPIOA->CRL &= ~GPIO_CRL_CNF1;
}

void set_port_b9_as_output(void)
{
	GPIOB->CRH |= GPIO_CRH_MODE9;
	GPIOB->CRH &= ~GPIO_CRH_CNF9;
}

void initialize(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN;
	set_port_a1_as_output();
	set_port_b9_as_output();
}
