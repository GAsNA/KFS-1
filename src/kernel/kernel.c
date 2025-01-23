#include "kernel.h"

t_terminal terminal;

static t_screen init_screen(void)
{
	t_screen screen;

	screen.buffer[0] = '\0';
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
	terminal.numslock = 1;
	terminal.to_escape = 0;
}

void main(void)
{
	init_terminal();

	clear_terminal();

	print_on_terminal("42 - rleseur\n\n", LIGHT_BLUE);

	printk(KERN_ERR "This is a printk ERR test.\n");
	printk(KERN_DEFAULT "This a printk DEFAULT test.\n");
	printk(KERN_WARNING "This is a printk WARNING test.\n\n");

	print_on_terminal("You can write now:\n", GREEN);

	//move_cursor(5);

	while(1)
		simulate_keyboard_interrupt();

	return;
}
