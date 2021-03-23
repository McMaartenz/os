#ifndef H_SCANCODE_TRANSLATOR
#define H_SCANCODE_TRANSLATOR

#include <stdint.h>

namespace QWERTY_layout
{
	#define shift_l 0x2A
	#define shift_r 0x36
        #define enter 0x1C
	#define backspace 0x0E
	#define space 0x39

	extern const char ASCII_table[];
	char translate(uint8_t, bool);
}

#endif
