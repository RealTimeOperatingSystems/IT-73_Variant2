#include "show_text.h"
#include "delay.h"
#include "microcontroller_setup.h"

int word_delay = 5000;
char name[] = "Alexander";
int word_length =  (sizeof(name)/sizeof(*name)) - 1; //last: \0

int main(void)
{	
	configure_registers();
	while(1)
	{
		if(get_b9())
		{	
			show_word(name, word_length);
			delay(word_delay);
		}
		else
		{
			c14_off();
		}
	}
}
