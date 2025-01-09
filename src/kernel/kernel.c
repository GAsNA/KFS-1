#include "kernel.h"

t_terminal terminal =	{
				.vidptr = (char*)0xb8000,
				.current_loc = 0,
				.shift = 0,
				.capslock = 0,
				.numslock = 0,
			};

void main(void)
{
	blank_console();

	printk("42 - rleseur", BLUE);
	newline_on_console();

	newline_on_console();

	printk("You can write now:", GREEN);
	newline_on_console();

	while(1)
		simulate_keyboard_interrupt();

	return;
}
