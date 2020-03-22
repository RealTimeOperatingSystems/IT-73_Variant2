#include "initialization.h"
#include "blink.h"
#include "delay.h"

int main(void)
{	
	initialize();
	
	for(;;)
	{
		b9_on();
		a1_on();
		
		delay(5);
		
		b9_off();
		
		delay(5);
		
		a1_off();
		
		delay(10);
	}
}
