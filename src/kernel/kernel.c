#include "kernel.h"

t_terminal terminal;

static t_screen init_screen(void)
{
	t_screen screen;

	screen.buffer = "";
	screen.current_loc = 0;
	
	return screen;
}

static void init_terminal(void)
{
	terminal.vidptr = (char*)BEGIN_VGA;
	terminal.current_screen = 0;
	
	int i = 0;
	while (i++ < LIMIT_NB_SCREENS)
		terminal.screens[i] = init_screen();

	terminal.current_loc = 0;
	terminal.shift = 0;
	terminal.capslock = 0;
	terminal.numslock = 0;
}

void main(void)
{
	init_terminal();

	clear_console();

	print_on_console("42 - rleseur\n\n", LIGHT_BLUE);

	print_on_console("You can write now:\n", GREEN);

	while(1)
		simulate_keyboard_interrupt();

	return;
}
