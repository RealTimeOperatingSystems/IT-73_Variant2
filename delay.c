#include "delay.h"

const int ms_delay = 2*0x40000 / 300;

void delay(int milliseconds)
{
	int delay = milliseconds * ms_delay;
	for(int i = 0; i < delay; i++){}
}
