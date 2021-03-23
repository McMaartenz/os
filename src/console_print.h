#ifndef H_CONSOLE_PRINT
#define H_CONSOLE_PRINT

#include <stdint.h>

#include "math.h"
#include "framebuffer.h"
#include "basic_font.h"

class console_print
{
public:
	console_print(Framebuffer*, PSF1_FONT*, unsigned int = 0xFFFFFFFF, unsigned int = 0x00000000);
	point cursor_position = {0, 0};
	Framebuffer* fb;
	PSF1_FONT* font;
	unsigned int color, clear_color;
	void put_char(char, unsigned int, unsigned int);
	void put_char(char);
	void print(const char*);
	void clear();
	void clear_char();
	void set_color(uint32_t);
	void set_position(point);
};

extern console_print* console;

#endif
