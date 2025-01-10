#include "kernel.h"

//void add_to_console_buffer_at_pos(char c, int color, int *pos)
//{
//	terminal.vidptr[(*pos)++] = c;
//	terminal.vidptr[(*pos)++] = color;
//}

//void add_to_console_and_screen_buffer_at_pos(char c, int color, int *pos)
//{
//	t_screen	*current_screen = &terminal.screens[terminal.current_screen];
//
//	add_to_screen_buffer_at_pos(c, color, current_screen, pos);
//
//	(*pos) -= 2;
//
//	add_to_console_buffer_at_pos(c, color, pos);
//}

/**
 * Blank the entire console
 *
 * @return void
 */
void clear_console(void)
{
	unsigned int i = 0;

	/* this loops clears the screen
	 * there are 25 lines each of 80 columns;
	 * each element takes 2 bytes */
	while(i < SCREENSIZE)
	{
		terminal.vidptr[i++] = ' ';
		terminal.vidptr[i++] = LIGHT_GRAY;
	}
}

/**
 * Add a newline on the console ('\n')
 *
 * @return void
 */
void newline_on_console(void)
{
	unsigned int line_size = BYTES_FOR_ELEMENT * NB_COLUMNS;
	terminal.current_loc += line_size - terminal.current_loc % line_size;
}

/**
 * Delete a char on the console ('\b')
 *
 * @return void
 */
void delete_on_console(void)
{
	if (terminal.current_loc - 2 >= 0)
	{
		terminal.vidptr[terminal.current_loc - 2] = '\0';
		terminal.current_loc -= 2;
	}
}

/**
 * Add a tab on the console ('\t')
 *
 * @return void
 */
void tab_on_console(void)
{
	int i = 0;
	while (i++ < TAB_SIZE)
		printk_char(' ', LIGHT_GRAY);
}

/**
 * Print a char on the console
 *
 * @param c char to display
 * @param color color of the char to display
 * @return void
 */
void printk_char(char c, int color)
{
	add_to_current_screen_buffer(c);

	if (c == '\n')
	{
		newline_on_console();
		return;
	}
	if (c == '\b')
	{
		delete_on_console();
		return;
	}
	if (c == '\t')
	{
		tab_on_console();
		return;
	}
	
	terminal.vidptr[terminal.current_loc++] = c;
	terminal.vidptr[terminal.current_loc++] = color;
}

/**
 * Print a string on the console
 *
 * @param str string to display
 * @param color color of the str to display
 * @return void
 */
void printk(char *str, int color)
{
	unsigned int i = 0;

	/* this loop writes the string to video memory */
	while(str[i] != '\0')
		printk_char(str[i++], color);
}
