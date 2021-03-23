#include "keyboard.h"
#include "../panic.h"

bool is_shift_l_down;
bool is_shift_r_down;

void handle_keyboard(uint8_t scancode)
{
	switch(scancode)
	{
	case space:
		console->put_char(' ');
		return;

	case shift_l:
		is_shift_l_down = true;
		return;

	case shift_l + 0x80:
		is_shift_l_down = false;
		return;

	case shift_r:
		is_shift_r_down = true;
		return;

	case shift_r + 0x80:
		is_shift_r_down = false;
		return;

	case enter:
		console->print("\n\r");
		return;

	case backspace:
		console->clear_char();
		return;
	}
	
	char ascii = QWERTY_layout::translate(scancode, is_shift_l_down || is_shift_r_down);
	if (ascii != 0)
	{
		console->put_char(ascii);
	}
}
