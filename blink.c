#include "blink.h"

void a1_on(void)
{
	int *GPIO_A_ODR = (int*)0x4001080C;	
	*GPIO_A_ODR = 0x00000002;
}

void a1_off(void)
{
	int *GPIO_A_ODR = (int*)0x4001080C;	
	*GPIO_A_ODR = 0x00000000;
}

void b9_on(void)
{
	int *GPIO_B_ODR = (int*)0x40010C0C;	
	*GPIO_B_ODR = 0x00000200;
}

void b9_off(void)
{
	int *GPIO_B_ODR = (int*)0x40010C0C;	
	*GPIO_B_ODR = 0x00000000;
}
