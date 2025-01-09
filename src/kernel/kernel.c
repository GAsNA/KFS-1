#include "kernel.h"

t_terminal terminal;

static t_screen init_screen(void)
{
	t_screen screen;

	screen.current_loc = 0;
	
	return screen;
}

static void init_terminal(void)
{
	terminal.vidptr = (char*)0xb8000;
	terminal.current_screen = 0;
	terminal.screens[0] = init_screen();
	terminal.current_loc = 0;
	terminal.shift = 0;
	terminal.capslock = 0;
	terminal.numslock = 0;
}

void main(void)
{
	init_terminal();

	clear_console();

	printk("42 - rleseur", LIGHT_BLUE);
	newline_on_console();

	newline_on_console();

	printk("You can write now:", GREEN);
	newline_on_console();

	while(1)
		simulate_keyboard_interrupt();

	return;
}
