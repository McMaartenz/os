#ifndef H_IDT
#define H_IDT

#define IDT_TA_INT_gate  0b10001110
#define IDT_TA_call_gate 0b10001100
#define IDT_TA_trap_gate 0b10001111

#include <stdint.h>

// IDT interrupt descriptor table
struct IDT_desc_entry
{
	uint16_t offset_0;
	uint16_t selector;
	uint8_t ist; // interrupt stack table offset
	uint8_t type_attr;
	uint16_t offset_1;
	uint32_t offset_2;
	uint32_t ignore;

	void set_offset(uint64_t);
	uint64_t get_offset();
}__attribute__((packed));

struct IDTR
{
	uint16_t limit;
	uint64_t offset;
}__attribute__((packed));

#endif
