#include "kernel_util.h"

extern "C" void _start(boot_info* k_args)
{
	kernel_info k_info = initialize_kernel(k_args);
	
	page_table_mgr* pt_mgr = k_info.pt_mgr;

	console->set_position({0, 0});
	console->clear_color = 0xFFFFFFFF;
	console->clear();
	console->color = 0x00000000;
	console->print("Kernel initialized successfully\n\r");

	while(1);
}

