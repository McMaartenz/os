#include "paging.h"

void page_directory_entry::set_flag(page_table_flag flag, bool value)
{
	uint64_t bit_selector = (uint64_t)1 << flag;
	this->value &= ~bit_selector;
	if (value)
	{
		this->value |= bit_selector;
	}
}

bool page_directory_entry::get_flag(page_table_flag flag)
{
	uint64_t bit_selector = (uint64_t)1 << flag;
	return (value & bit_selector > 0);
}

uint64_t page_directory_entry::get_addr()
{
	return (value & 0x000ffffffffff000) >> 12;
}

void page_directory_entry::set_addr(uint64_t addr)
{
	addr &= 0x000000ffffffffff;
	value &= 0xfff0000000000fff;
	value |= (addr << 12);
}
