#include "initialization.h"

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

void set_port_b9_as_output(void)
{
	int *GPIO_B_CRH = (int*)0x40010C04;	
	*GPIO_B_CRH = 0x00000030;
}

void initialize(void)
{
	enable_ports_a_b();
	set_port_a1_as_output();
	set_port_b9_as_output();
}
