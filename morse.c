#include "morse.h"

const int letter_delay = 5000;
const int short_signal_delay = 1000;
const int long_signal_delay = 2000;
const int between_signal_delay = 3000;

const DelayEnum a[] = {Short, Long};
const DelayEnum b[] = {Long, Short, Short, Short};
const DelayEnum c[] = {Long, Short, Long, Short};
const DelayEnum d[] = {Long, Short, Short};
const DelayEnum e[] = {Short};
const DelayEnum f[] = {Short, Short, Long, Short};
const DelayEnum g[] = {Long, Long, Short};
const DelayEnum h[] = {Short, Short, Short, Short};
const DelayEnum i[] = {Short, Short};
const DelayEnum j[] = {Short, Long, Long, Long};
const DelayEnum k[] = {Long, Short, Long};
const DelayEnum l[] = {Short, Long, Short, Short};
const DelayEnum m[] = {Long, Long};
const DelayEnum n[] = {Long, Short};
const DelayEnum o[] = {Long, Long, Long};
const DelayEnum p[] = {Short, Long, Long, Short};
const DelayEnum q[] = {Long, Long, Short, Long};
const DelayEnum r[] = {Short, Long, Short};
const DelayEnum s[] = {Short, Short, Short};
const DelayEnum t[] = {Long};
const DelayEnum u[] = {Short, Short, Long};
const DelayEnum v[] = {Short, Short, Short, Long};
const DelayEnum w[] = {Short, Long, Long};
const DelayEnum x[] = {Long, Short, Short, Long};
const DelayEnum y[] = {Long, Short, Long, Long};
const DelayEnum z[] = {Long, Long, Short, Short};

const MorseSymbolInfo morseCodes[] =
{
	{.length = 2, .row = a},
	{.length = 4, .row = b},
	{.length = 4, .row = c},
	{.length = 3, .row = d},
	{.length = 1, .row = e},
	{.length = 4, .row = f},
	{.length = 3, .row = g},
	{.length = 4, .row = h},
	{.length = 2, .row = i},
	{.length = 4, .row = j},
	{.length = 3, .row = k},
	{.length = 4, .row = l},
	{.length = 2, .row = m},
	{.length = 2, .row = n},
	{.length = 3, .row = o},
	{.length = 4, .row = p},
	{.length = 4, .row = q},
	{.length = 3, .row = r},
	{.length = 3, .row = s},
	{.length = 1, .row = t},
	{.length = 3, .row = u},
	{.length = 4, .row = v},
	{.length = 3, .row = w},
	{.length = 4, .row = x},
	{.length = 4, .row = y},
	{.length = 4, .row = z}
};

MorseSymbolInfo get_symbol_info(char symbol)
{
	int letterIndex;
    if(symbol <= 'Z')
	{
        letterIndex = symbol - 'A';
    }
    else
    {
        letterIndex = symbol - 'a';
    }
    return morseCodes[letterIndex];
}
