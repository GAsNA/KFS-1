#ifndef KEYBOARD_H
# define KEYBOARD_H

extern char	read_port(unsigned short port);
extern void	write_port(unsigned short port, unsigned char data);
extern void	load_idt(long unsigned int* idt_address);
extern void	keyboard_handler();

# define IDT_SIZE 256 // Specific to x86 architecture
# define KEYBOARD_DATA_PORT 0x60
# define KEYBOARD_STATUS_PORT 0x64
# define KERNEL_CODE_SEGMENT_OFFSET 0x08
# define INTERRUPT_GATE 0x8e
# define ENTER_KEY_CODE 0x1c

struct IDT_entry{
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};

extern struct IDT_entry IDT[IDT_SIZE];

void kb_init(void);
void idt_init(void);

#endif
