#include "kernel.h"
#include "color.h"

t_terminal terminal =	{
				.vidptr = (char*)0xb8000,
				.current_loc = 0,
				.shift = 0,
				.capslock = 0,
				.numslock = 0,
			};

void main(void)
{
	blank_screen();

	char *str = "42 - rleseur";
	printk(str, BLUE);
	newline_on_screen();

	newline_on_screen();

	printk("You can write now:", GREEN);
	newline_on_screen();

	idt_init();
	kb_init();

	while(1);

	return;
}
