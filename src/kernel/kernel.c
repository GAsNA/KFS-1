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
	{
		terminal.screens[i] = init_screen();
		//add_str_to_screen()
	}

	terminal.current_loc = 0;
	terminal.shift = 0;
	terminal.capslock = 0;
	terminal.numslock = 1;
}

void main(void)
{
	init_terminal();

	clear_console();

	print_on_console("42 - rleseur\n\n", LIGHT_BLUE);

	print_on_console("You can write now:\n", GREEN);

	//printk(KERN_ERR "Ceci est un test ERR de printk\n");
	//printk(KERN_DEFAULT "Ceci est un test DEFAULT de printk\n");
	//printk(KERN_WARNING "Ceci est un test WARNING de printk: %s, %i, %d, %x, %c, %%\n", "ARGS", 42, 42 * 2, 42, 'B');
	//printk("TEST ARGS: %c, %c\n", 'b', 'c');
	printk("TEST: %s, %s\n", "ARGS", "EHEH");

	while(1)
		simulate_keyboard_interrupt();

	return;
}
