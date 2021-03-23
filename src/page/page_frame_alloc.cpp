#include "page_frame_alloc.h"
#include "../console_print.h"
#include "../cstr.h"

uint64_t mem_free,
	 mem_used,
	 mem_reserved;

uint64_t page_bf_i = 0;

bool initialized = false;

page_frame_alloc global_alloc;

void page_frame_alloc::read_efi_memory_map(EFI_MEMORY_DESCRIPTOR* mem_map, size_t mem_map_size, size_t mem_map_descriptor_size)
{
	if (initialized) return;
	initialized = true;
	console->set_color(0xFF55FF55);
	console->print("Initializing efi memory map\n\r");	
	uint64_t mem_map_entries = mem_map_size / mem_map_descriptor_size;

	void* mem_free_seg_largest = NULL;
	size_t mem_free_seg_largest_size = 0;

	console->print("Starting big for loop\n\r");	
	for (int i = 0; i < mem_map_entries; i++)
	{
		EFI_MEMORY_DESCRIPTOR* descriptor = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mem_map + (i * mem_map_descriptor_size));
		if (descriptor->type == 7) // efi_conventional_memory
		{
			if (descriptor->page_count * 4096 > mem_free_seg_largest_size)
			{
				mem_free_seg_largest = descriptor->physical_addr;
				mem_free_seg_largest_size = descriptor->page_count * 4096;
			}	
		}
	}

	console->print("getting memory size\n\r");	
	uint64_t mem_size = get_memory_size(mem_map, mem_map_entries, mem_map_descriptor_size);
	mem_free = mem_size;
	uint64_t bitfield_size = mem_size / 4096 / 8 + 1;
	console->print("Initializing bitfield\n\r");	
	console->print("MEMORY SIZE: ");
	console->print(to_s((uint64_t)mem_size));
	console->print(", BITFIELD SIZE: ");
	console->print(to_s((uint64_t)bitfield_size));
	console->print("\n\r");
	
	// Initialize bitfield
	initialize_bitfield(bitfield_size, mem_free_seg_largest);

	console->print("Locking pages of bitfield\n\r");
	// Lock pages of bitfield & reserve pages of unusable or reserved memory
	pages_lock(page_bf.buffer, page_bf.size / 4096 + 1);
	
	console->print("Reserving pages of unusable/reserved memory\n\r");	
	for (int i = 0; i < mem_map_entries; i++)
	{
		EFI_MEMORY_DESCRIPTOR* descriptor = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mem_map + (i * mem_map_descriptor_size));
		if (descriptor->type != 7) // not efi_conventional_memory
		{
			pages_reserve(descriptor->physical_addr, descriptor->page_count);
		}
	}	
	console->print("Done\n\r");	

}

void page_frame_alloc::initialize_bitfield(size_t bf_size, void* buffer_addr)
{	
	console->print("Initializing bitfield now\n\r");
	page_bf.size = bf_size;
	page_bf.buffer = (uint8_t*)buffer_addr;
	console->print("bitfield_size: ");
	console->print(to_s((int64_t)bf_size));
	console->print("\n\rbuffer addr: ");
	console->print(to_s((uint64_t)buffer_addr));
	console->print("\n\rStarting for loop\n\r");
	for (int i = 0; i < bf_size; i++)
	{
		*(uint8_t*)(page_bf.buffer + i) = 0;
	}
	console->print("for loop is done\n\r");
}

void page_frame_alloc::page_free(void* addr)
{
	uint64_t i = (uint64_t)addr / 4096;
	if (page_bf[i] == false || !page_bf.set(i, false)) return;
	mem_free += 4096;
	mem_used -= 4096;
	if (page_bf_i > i) page_bf_i = i;	
}

void page_frame_alloc::page_lock(void* addr)
{
	uint64_t i = (uint64_t)addr / 4096;
	if (page_bf[i] == true || !page_bf.set(i, true)) return;
	mem_free -= 4096;
	mem_used += 4096;
}

void page_frame_alloc::page_unreserve(void* addr)
{
	uint64_t i = (uint64_t)addr / 4096;
	if (page_bf[i] == false || !page_bf.set(i, false)) return;
	mem_free += 4096;
	mem_reserved -= 4096;	
	if (page_bf_i > i) page_bf_i = i;
}

void page_frame_alloc::page_reserve(void* addr)
{
	uint64_t i = (uint64_t)addr / 4096;
	if (page_bf[i] == true || !page_bf.set(i, true)) return;
	mem_free -= 4096;
	mem_reserved += 4096;
}

void page_frame_alloc::pages_free(void* addr, uint64_t page_count)
{
	for (int i = 0; i < page_count; i++)
	{
		page_free((void*)((uint64_t)addr + (i * 4096)));
	}
}

void page_frame_alloc::pages_lock(void* addr, uint64_t page_count)
{
	console->print("About to lock ");
	console->print(to_s((uint64_t)page_count));
	console->print(" pages.\n\r");
	for (int i = 0; i < page_count; i++)
	{
		page_lock((void*)((uint64_t)addr + (i * 4096)));
	}
	console->print("done!\n\r");
}

void page_frame_alloc::pages_unreserve(void* addr, uint64_t page_count)
{
	for (int i = 0; i < page_count; i++)
	{
		page_unreserve((void*)((uint64_t)addr + (i * 4096)));
	}
}

void page_frame_alloc::pages_reserve(void* addr, uint64_t page_count)
{
	for (int i = 0; i < page_count; i++)
	{
		page_reserve((void*)((uint64_t)addr + (i * 4096)));
	}	
}

uint64_t page_frame_alloc::get_mem_free()
{
	return mem_free;
}

uint64_t page_frame_alloc::get_mem_used()
{
	return mem_used;
}

uint64_t page_frame_alloc::get_mem_reserved()
{
	return mem_reserved;
}

void* page_frame_alloc::page_request()
{
	for (; page_bf_i < page_bf.size * 8; page_bf_i++)
	{
		if (page_bf[page_bf_i] == true) continue;
		page_lock((void*)(page_bf_i * 4096));
		return (void*)(page_bf_i * 4096);
	}

	// panic: no memory available to request
	return NULL;
}
