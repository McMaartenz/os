[bits 64]

load_GDT:
	lgdt [rdi]
	mov ax, 0x10 ; put kernel data seg
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	pop rdi
	mov rax, 0x08 ; put kernel code seg
	push rax
	push rdi
	retfq ; far 64-bit return

GLOBAL load_GDT
