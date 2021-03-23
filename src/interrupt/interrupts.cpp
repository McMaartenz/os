#include "interrupts.h"

void PIC_end_master()
{
	byte_out(PIC1_CMD, PIC_EOI);
	panic("q");
}

void PIC_end_slave()
{
	byte_out(PIC2_CMD, PIC_EOI);
	byte_out(PIC1_CMD, PIC_EOI);
}

void PIC_remap()
{
	// Talk to le PIC chip
	uint8_t master, slave;

	master = byte_in(PIC1_DAT);
	io_wait();
	slave = byte_in(PIC2_DAT);
	io_wait();	
	
	byte_out(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
	io_wait();
	byte_out(PIC2_CMD, ICW1_INIT | ICW1_ICW4);
	io_wait();

	byte_out(PIC1_DAT, 0x20);
	io_wait();
	byte_out(PIC2_DAT, 0x28);
	io_wait();

	byte_out(PIC1_DAT, 4);
	io_wait();
	byte_out(PIC2_DAT, 2);
	io_wait();

	byte_out(PIC1_DAT, ICW4_8086);
	io_wait();
	byte_out(PIC2_DAT, ICW4_8086);
	io_wait();

	byte_out(PIC1_DAT, master);
	io_wait();
	byte_out(PIC2_DAT, slave);	
}

__attribute__((interrupt)) void handler_page_fault(struct int_frame* frame)
{
	panic("Page fault");
}

__attribute__((interrupt)) void handler_double_fault(struct int_frame* frame)
{
	panic("Double fault");
}

__attribute__((interrupt)) void handler_general_protection_fault(struct int_frame* frame)
{
	panic("General protection fault");
}

__attribute__((interrupt)) void handler_keyboard(struct int_frame* frame)
{
	uint8_t scancode = byte_in(0x60);
	handle_keyboard(scancode);
	PIC_end_master();
}
