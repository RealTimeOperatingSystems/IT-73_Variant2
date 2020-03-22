#include "show_text.h"
#include "microcontroller_setup.h"
#include "delay.h"

void delay_for_signal(DelayEnum signal_type)
{
	if(signal_type == Short)
	{
		delay(short_signal_delay);
	}
	else
	{
		delay(long_signal_delay);
	}
}

void show_letter(char symbol)
{
	MorseSymbolInfo letterInfo = get_symbol_info(symbol);
	int signals_count = letterInfo.length;
	for(int i = 0; i < signals_count; i++)
	{
		DelayEnum current_signal_type = *(letterInfo.row + i);
		
		a1_on();		
		delay_for_signal(current_signal_type);		
		a1_off();
		delay(between_signal_delay);
	}
}

void show_word(char* text, int length)
{
	for(int i = 0; i < length; i++)
	{
		char currentLetter = *(text+i);
		show_letter(currentLetter);
		delay(letter_delay);
	}
}
