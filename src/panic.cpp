#include "panic.h"

void panic(const char* panic_msg)
{
	console->clear_color = 0xFFF54242;
	console->clear();
	console->set_color(0xFFFFFFFF);
	console->set_position({console->fb->width / 2 - 14*8, console->fb->height / 2 - 32});
	console->print(":( Unrecoverable kernel panic");
	console->set_position({console->fb->width / 2 - (7 + str_length(panic_msg)) * 8 / 2, console->fb->height / 2});
	console->print("More info: ");
	console->print(panic_msg);
	while(1);
}
