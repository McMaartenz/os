#include "console_print.h"

console_print* console;

console_print::console_print(Framebuffer* fb, PSF1_FONT* font, unsigned int color, unsigned int clear_color)
{
	this->fb = fb;
	this->font = font;
	this->color = color;
	this->clear_color = clear_color;
}

void console_print::clear()
{
	uint64_t fb_base = (uint64_t)fb->baseAddr;
       	uint64_t bytes_per_scln = fb->ppscln * 4;
	uint64_t fb_height = fb->height;
	uint64_t fb_size = fb->bufferSize;

	for (int vscln = 0; vscln < fb_height; vscln++)
	{
		uint64_t pixel_ptr_base = fb_base + (bytes_per_scln * vscln);
		for (uint32_t* pixel_ptr = (uint32_t*)pixel_ptr_base; pixel_ptr < (uint32_t*)(pixel_ptr_base + bytes_per_scln); pixel_ptr++)
		{
			*pixel_ptr = clear_color;
		}
	}
}

void console_print::put_char(char chr, unsigned int x_offset, unsigned int y_offset)
{
	unsigned int* pixel_ptr = (unsigned int*)fb->baseAddr;
	char* font_ptr = (char*)font->glyph_buffer + (chr * font->psf1_header->char_size);
	for (unsigned long y = y_offset; y < y_offset + 16; y++)
	{
		for (unsigned long x = x_offset; x < x_offset + 8; x++)
		{
			if ((*font_ptr & (0b10000000 >> (x - x_offset))) > 0)
			{
				*(unsigned int*)(pixel_ptr + x + (y * fb->ppscln)) = color;
			}
		}
		font_ptr++;
	}
}

void console_print::put_char(char chr)
{
	put_char(chr, cursor_position.x, cursor_position.y);
	cursor_position.x += 8;
	if (cursor_position.x + 8 > fb->width)
	{
		cursor_position.x = 0;
		cursor_position.y += 16;
	}
}

void console_print::print(const char* text)
{
	unsigned int x = 0;
	char* chr = (char*)text;
	while(*chr != 0)
	{
		if (*chr == '\n')
		{
			cursor_position.y += 16;
		}
		else if (*chr == '\r')
		{
			cursor_position.x = 0;
		}
		else
		{
			put_char(*chr, cursor_position.x, cursor_position.y);	
			cursor_position.x += 8;
			if (cursor_position.x + 8 > fb->width)
			{
				cursor_position.x = 0;
				cursor_position.y += 16;
			}
		}
		chr++;	
	}
}

void console_print::set_color(uint32_t color)
{
	this->color = color;
}

void console_print::set_position(point position)
{
	this->cursor_position = position;
}

void console_print::clear_char()
{
	if (cursor_position.x == 0)
	{
		cursor_position.x = fb->width;
		cursor_position.y -= 16;
		if (cursor_position.y < 0)
		{
			cursor_position.y = 0;
		}
	}

	unsigned int x_offset = cursor_position.x;
	unsigned int y_offset = cursor_position.y;

	unsigned int* pixel_ptr = (unsigned int*)fb->baseAddr;
	for (unsigned long y = y_offset; y < y_offset + 16; y++)
	{
		for (unsigned long x = x_offset - 8; x < x_offset; x++)
		{
			*(unsigned int*)(pixel_ptr + x + (y * fb->ppscln)) = clear_color;
		}
	}

	cursor_position.x -= 8;
	if (cursor_position.x < 0)
	{
		cursor_position.x = fb->width;
		cursor_position.y -= 16;
		if (cursor_position.y < 0)
		{
			cursor_position.y = 0;
		}
	}
}
