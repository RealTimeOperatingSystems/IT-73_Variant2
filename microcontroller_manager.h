#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


void enable_port_c_clock(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}


void enable_port_b_clock(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void enable_output_pin(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void enable_input_pin(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void set_up_microcontroller(void)
{	
	enable_port_c_clock();
	enable_port_b_clock();
	enable_output_pin();
	enable_input_pin();
}

void led_on(void)
{
	 GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void led_off(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}
