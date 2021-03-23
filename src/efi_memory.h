#ifndef H_EFI_MEMORY
#define H_EFI_MEMORY

#include <stdint.h>

struct EFI_MEMORY_DESCRIPTOR
{
	uint32_t type;
	void* physical_addr, *virtual_addr;
	uint64_t page_count, attributes;
};

extern const char* EFI_MEMORY_TYPE_STRINGS[];

#endif
