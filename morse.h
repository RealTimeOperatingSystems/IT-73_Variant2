#ifndef MORSE_H
#define MORSE_H

typedef enum 
{
	Short, 
	Long
} DelayEnum;


extern const int letter_delay;
extern const int short_signal_delay;
extern const int long_signal_delay;
extern const int between_signal_delay;

typedef struct
{
	const int length;
	const DelayEnum* const row;
} MorseSymbolInfo;

extern const MorseSymbolInfo morseCodes[];

MorseSymbolInfo get_symbol_info(char symbol);

#endif
