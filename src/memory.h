#ifndef H_MEMORY
#define H_MEMORY

#include <stdint.h>
#include "efi_memory.h"

uint64_t get_memory_size(EFI_MEMORY_DESCRIPTOR*, uint64_t, uint64_t);
void set_memory(void*, uint8_t, uint64_t);

#endif
