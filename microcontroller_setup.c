#include "microcontroller_setup.h"

void enable_ports_a_b(void)
{
	int *ptr_RCC_APB2ENR = (int*)0x40021018;	
	*ptr_RCC_APB2ENR |= 0x000C;
}

void set_port_a1_as_output(void)
{
	int *GPIO_A_CRL = (int*)0x40010800;	
	*GPIO_A_CRL = 0x00000030;
}

void set_port_b9_as_input(void)
{
	int *GPIO_B_CRH = (int*)0x40010C04;	
	*GPIO_B_CRH = 0x00000080;
}

void configure_registers(void)
{
	enable_ports_a_b();
	set_port_a1_as_output();
	set_port_b9_as_input();
}

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

int get_b9(void)
{
	const int *GPIO_B_IDR = (const int*)0x40010C08;	
	return *GPIO_B_IDR & 0x0200;
}
