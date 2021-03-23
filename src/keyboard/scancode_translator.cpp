#include "scancode_translator.h"

namespace QWERTY_layout
{
	const char ASCII_table[] =
	{
		0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
		'-', '=', 0, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
		'o', 'p', '[', ']', 0, 0, 'a', 's', 'd', 'f', 'g', 'h',
		'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c',
		'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
	};

	char translate(uint8_t scancode, bool is_upper)
	{
		if (scancode > 58) return 0; // cannot handle
		
		if (is_upper)
		{
			return ASCII_table[scancode] - 32;
		}
		return ASCII_table[scancode];
	}
}
