#include "microcontroller_setup.h"

void enable_ports_b_c(void)
{
	int *ptr_RCC_APB2ENR = (int*)0x40021018;	
	*ptr_RCC_APB2ENR |= 0x0018;
}

void set_port_c14_as_output(void)
{
	int *GPIO_C_CRH = (int*)0x40011004;	
	*GPIO_C_CRH = 0x03000000;
}

void set_port_b9_as_input(void)
{
	int *GPIO_B_CRH = (int*)0x40010C04;	
	*GPIO_B_CRH = 0x00000080;
}

void configure_registers(void)
{
	enable_ports_b_c();
	set_port_c14_as_output();
	set_port_b9_as_input();
}

void c14_on(void)
{
	int *GPIO_C_ODR = (int*)0x4001100C;	
	*GPIO_C_ODR = 0x00004000;
}

void c14_off(void)
{
	int *GPIO_C_ODR = (int*)0x4001100C;	
	*GPIO_C_ODR = 0x00000000;
}

int get_b9(void)
{
	const int *GPIO_B_IDR = (const int*)0x40010C08;	
	return *GPIO_B_IDR & 0x0200;
}
