#ifndef SHOW_TEXT_H
#define SHOW_TEXT_H
#include "morse.h"

void delay_for_signal(DelayEnum signal_type);
void show_letter(char symbol);
void show_word(char* text, int length);

#endif
