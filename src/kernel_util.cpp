#include "kernel_util.h"

kernel_info k_info;
page_table_mgr pt_mgr = NULL;
void prepare_memory(boot_info* k_args)
{
	int64_t mem_map_entries = k_args->mem_map_size / k_args->mem_map_descriptor_size;

	global_alloc = page_frame_alloc();
	global_alloc.read_efi_memory_map(k_args->mem_map, k_args->mem_map_size, k_args->mem_map_descriptor_size);

	uint64_t kernel_size = (uint64_t)&_kernel_end - (uint64_t)&_kernel_start;
	uint64_t pages_kernel = (uint64_t)kernel_size / 4096 + 1;

	global_alloc.pages_lock(&_kernel_start, pages_kernel);

	page_table* PML4 = (page_table*)global_alloc.page_request();
	set_memory(PML4, 0, 0x1000);
	

	pt_mgr = page_table_mgr(PML4);

	for (uint64_t i = 0; i < get_memory_size(k_args->mem_map, mem_map_entries, k_args->mem_map_descriptor_size); i += 0x1000)
	{
		pt_mgr.map_memory((void*)i, (void*)i);	
	}
	uint64_t fb_base_addr = (uint64_t)k_args->fb->baseAddr;
	uint64_t fb_size = (uint64_t)k_args->fb->bufferSize + 0x1000;

	global_alloc.pages_lock((void*)fb_base_addr, fb_size / 0x1000 + 1);
	for (uint64_t i = fb_base_addr; i < fb_base_addr + fb_size; i += 4096)
	{
		pt_mgr.map_memory((void*)i, (void*)i);	
	}
	asm ("mov %0, %%cr3" : : "r" (PML4));

	k_info.pt_mgr = &pt_mgr;
}

IDTR idtr;
void prepare_int()
{
	idtr.limit = 0x0fff;
	idtr.offset = (uint64_t)global_alloc.page_request();

	IDT_desc_entry* int_page_fault = (IDT_desc_entry*)(idtr.offset + 0xE * sizeof(IDT_desc_entry));	
	int_page_fault->set_offset((uint64_t)handler_page_fault);
	int_page_fault->type_attr = IDT_TA_INT_gate;
	int_page_fault->selector = 0x08; // kernel code selector

	IDT_desc_entry* int_double_fault = (IDT_desc_entry*)(idtr.offset + 0x8 * sizeof(IDT_desc_entry));	
	int_double_fault->set_offset((uint64_t)handler_double_fault);
	int_double_fault->type_attr = IDT_TA_INT_gate;
	int_double_fault->selector = 0x08; // kernel code selector

	IDT_desc_entry* int_general_protection_fault = (IDT_desc_entry*)(idtr.offset + 0xD * sizeof(IDT_desc_entry));	
	int_general_protection_fault->set_offset((uint64_t)handler_general_protection_fault);
	int_general_protection_fault->type_attr = IDT_TA_INT_gate;
	int_general_protection_fault->selector = 0x08; // kernel code selector

	IDT_desc_entry* int_keyboard = (IDT_desc_entry*)(idtr.offset + 0x21 * sizeof(IDT_desc_entry));	
	int_keyboard->set_offset((uint64_t)handler_keyboard);
	int_keyboard->type_attr = IDT_TA_INT_gate;
	int_keyboard->selector = 0x08; // kernel code selector

	asm("lidt %0" : : "m" (idtr));

	PIC_remap();

	byte_out(PIC1_DAT, 0b11111101);
	byte_out(PIC2_DAT, 0b11111111);

	asm ("sti");
}

console_print r = console_print(NULL, NULL);
kernel_info initialize_kernel(boot_info* k_args)
{
	r = console_print(k_args->fb, k_args->font);
	console = &r;
	
	GDT_descriptor descriptor;
	descriptor.size = sizeof(GDT) - 1;
	descriptor.offset = (uint64_t)&default_GDT;
	load_GDT(&descriptor);
	console->print("Preparing memory\n\r");
	prepare_memory(k_args);
	console->print("Clearing buffer\n\r");
	set_memory(k_args->fb->baseAddr, 0, k_args->fb->bufferSize);
	console->print("Preparing interrupts\n\r");	
	prepare_int();
	console->print("all OK!\n\r");
	return k_info;
}
