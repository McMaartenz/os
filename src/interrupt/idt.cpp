#include "idt.h"

void IDT_desc_entry::set_offset(uint64_t offset)
{
	offset_0 = (uint16_t)(offset & 0x000000000000ffff);
	offset_1 = (uint16_t)((offset & 0x00000000ffff0000) >> 16);
	offset_2 = (uint32_t)((offset & 0xffffffff00000000) >> 32);
}

uint64_t IDT_desc_entry::get_offset()
{
	uint64_t offset = 0;
	offset |= (uint64_t)offset_0;
	offset |= (uint64_t)offset_1 << 16;
	offset |= (uint64_t)offset_2 << 32;
	return offset;
}
