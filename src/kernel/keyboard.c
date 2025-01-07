#include "kernel.h"
#include "keyboard_map.h"

struct IDT_entry IDT[IDT_SIZE];

void kb_init(void)
{
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	write_port(0x21 , 0xFD);
}

void idt_init(void)
{
	unsigned long keyboard_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	/* populate IDT entry of keyboard's interrupt */
	keyboard_address = (unsigned long)keyboard_handler; 
	IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = INTERRUPT_GATE;
	IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;
	

	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	write_port(0x20 , 0x11);
	write_port(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	write_port(0x21 , 0x20);
	write_port(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	write_port(0x21 , 0x00);  
	write_port(0xA1 , 0x00);  

	/* ICW4 - environment info */
	write_port(0x21 , 0x01);
	write_port(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	write_port(0x21 , 0xff);
	write_port(0xA1 , 0xff);

	/* fill the IDT descriptor */
	idt_address = (unsigned long)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	load_idt(idt_ptr);
}

void keyboard_handler_main(void) {
	unsigned char status;
	unsigned char keycode;

	t_key selected_key;
	char selected_char;

	int is_pressed = 1;

	/* write EOI */
	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);

		/* Check if key is pressed or not */
		if (keycode >= 0x80)
			is_pressed = 0;
		if (!is_pressed)
			keycode -= 0x80;
		
		/* Check if keycode is valid and is shift */
		if (keycode < 0)
			return;
		if (keycode == LSHIFT || keycode == RSHIFT)
		{
			if (is_pressed)
				terminal.shift = 1;
			else
				terminal.shift = 0;
			return;
		}
		
		/* If key is not pressed, do not write on terminal and return */
		if (!is_pressed)
			return;
		
		/* Check the keycode for non-printable char */
		if (keycode == ENTER)
		{
			newline_on_screen();
			return;
		}
		if (keycode == CAPSLOCK)
		{
			terminal.capslock = !terminal.capslock;
			return;
		}
		if (keycode == NUMSLOCK)
		{
			terminal.numslock = !terminal.numslock;
			return;
		}
	
		/* Selected the char given by inputs */
		selected_key = keyboard_map[keycode];

		if (terminal.numslock && selected_key.numslock != 0)
		{
			if (!terminal.shift)
				selected_char = selected_key.numslock;
			else
				return;
		}
		else if (terminal.capslock && selected_key.capital != 0)
		{
			if (terminal.shift)
				selected_char = selected_key.small;
			else
				selected_char = selected_key.capital;
		}
		else if (selected_key.small != 0)
		{
			if (terminal.shift)
				selected_char = selected_key.capital;
			else
				selected_char = selected_key.small;
		}
		else
		{
		//	printk(ft_itoa(keycode), MAGENTA);
			return;
		}

		/* Write on terminal the selected char */
		printk_char(selected_char, LIGHT_GRAY);
	}
}
