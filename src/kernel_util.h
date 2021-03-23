#ifndef H_KERNEL_UTIL
#define H_KERNEL_UTIL

#include <stddef.h>

#include "console_print.h"
#include "cstr.h"
#include "efi_memory.h"
#include "memory.h"
#include "bitfield.h"
#include "page/page_frame_alloc.h"
#include "page/page_map_indexer.h"
#include "page/paging.h"
#include "page/page_table_mgr.h"
#include "gdt/gdt.h"
#include "interrupt/idt.h"
#include "interrupt/interrupts.h"
#include "io.h"

struct boot_info
{
	Framebuffer* fb;
	PSF1_FONT* font;
	EFI_MEMORY_DESCRIPTOR* mem_map;
	uint64_t mem_map_size, mem_map_descriptor_size;
};

extern uint64_t _kernel_start;
extern uint64_t _kernel_end;

struct kernel_info
{
	page_table_mgr* pt_mgr;
};

kernel_info initialize_kernel(boot_info*);

#endif
