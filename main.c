#include "initialization.h"
#include "blink.h"
#include "delay.h"

const int T = 20;
const int a1_t = 10;
const int b9_t = 5;

int main(void)
{	
	initialize();
	
	for(;;)
	{
		b9_on();
		a1_on();
		
		if(a1_t < b9_t)
		{
			delay(a1_t);
			a1_off();
			
			delay(b9_t - a1_t);
			b9_off();
		
			delay(T - b9_t);
		}
		else
		{
			delay(b9_t);
			b9_off();
			
			delay(a1_t - b9_t);
			a1_off();
		
			delay(T - a1_t);
		}
	}
}
