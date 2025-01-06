#include "kernel.h"
#include "color.h"

t_terminal terminal =	{
							.vidptr = (char*)0xb8000,
							.current_loc = 0
						};

void blank_screen(void)
{
	unsigned int i = 0;

	/* this loops clears the screen
	 * there are 25 lines each of 80 columns;
	 * each element takes 2 bytes */
	while(i < SCREENSIZE) {
		/* blank character */
		terminal.vidptr[i++] = ' ';
		/* attribute-byte - light grey on black screen */
		terminal.vidptr[i++] = LIGHT_GRAY; 		
	}
}

void write_on_screen(char *str, int color)
{
	unsigned int i = 0;

	/* this loop writes the string to video memory */
	while(str[i] != '\0') {
		/* the character's ascii */
		terminal.vidptr[terminal.current_loc++] = str[i++];
		/* attribute-byte: give character black bg and light grey fg */
		terminal.vidptr[terminal.current_loc++] = color;
	}
}

void newline_on_screen(void)
{
	unsigned int line_size = BYTES_FOR_ELEMENT * NB_COLUMNS;
	terminal.current_loc += line_size - terminal.current_loc % line_size;
}

void main(void)
{
	char *str = "42 - rleseur";

	blank_screen();

	write_on_screen(str, BLUE);

	newline_on_screen();
	newline_on_screen();

	idt_init();
	kb_init();

	while(1);

	return;
}
