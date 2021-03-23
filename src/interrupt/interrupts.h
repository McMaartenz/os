#ifndef H_INTERRUPTS
#define H_INTERRUPTS

#define PIC1_CMD 0x20
#define PIC1_DAT 0x21
#define PIC2_CMD 0xA0
#define PIC2_DAT 0xA1
#define PIC_EOI 0x20

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

#include "../panic.h"
#include "../io.h"
#include "../cstr.h"
#include "../keyboard/keyboard.h"

void PIC_remap();
void PIC_end_master();
void PIC_end_slave();

struct int_frame;
__attribute__((interrupt)) void handler_page_fault(struct int_frame*);
__attribute__((interrupt)) void handler_double_fault(struct int_frame*);
__attribute__((interrupt)) void handler_general_protection_fault(struct int_frame*);
__attribute__((interrupt)) void handler_keyboard(struct int_frame*);

#endif
