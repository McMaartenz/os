#include "memory.h"

uint64_t get_memory_size(EFI_MEMORY_DESCRIPTOR* mem_map, uint64_t mem_map_entries, uint64_t mem_map_descriptor_size)
{
	static uint64_t memory_size_bytes = 0;

	if (memory_size_bytes > 0)
	{
		return memory_size_bytes;
	}

	for (int i = 0; i < mem_map_entries; i++)
	{
		EFI_MEMORY_DESCRIPTOR* descriptor = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mem_map + (i * mem_map_descriptor_size));
		memory_size_bytes += descriptor->page_count * 4096;	
	}

	return memory_size_bytes;
}

void set_memory(void* start_addr, uint8_t value, uint64_t byte_count)
{
	for (uint64_t i = 0; i < byte_count; i++)
	{
		*(uint8_t*)((uint64_t)start_addr + i) = value;
	}
}
