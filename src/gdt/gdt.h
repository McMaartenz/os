#ifndef H_GDT
#define H_GDT

#include <stdint.h>

struct GDT_descriptor
{
	uint16_t size;
	uint64_t offset;
}__attribute__((packed)); // Perform no optimization or place bits between items in this struct

struct GDT_entry
{
	uint16_t limit_0;
	uint16_t base_0;
	uint8_t base_1;
	uint8_t access_byte;
	uint8_t limit_1_flags;
	uint8_t base_2;	
}__attribute__((packed));

struct GDT
{
	GDT_entry null;
	GDT_entry kernel_code;
	GDT_entry kernel_data;
	GDT_entry user_null;
	GDT_entry user_code;
	GDT_entry user_data;	
}__attribute__((packed))
 __attribute__((aligned(0x1000)));

extern GDT default_GDT;
extern "C" void load_GDT(GDT_descriptor* descriptor);

#endif
