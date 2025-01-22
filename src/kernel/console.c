#include "kernel.h"

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
		terminal.vidptr[i++] = '\0';
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

	fb_move_cursor(terminal.current_loc / 2);
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

		fb_move_cursor(terminal.current_loc / 2);
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
		print_char_on_console(' ', LIGHT_GRAY);
}

/**
 * Print a char on the console
 *
 * @param c char to display
 * @param color color of the char to display
 * @return void
 */
void print_char_on_console(char c, int color)
{

	if (c == '\n')
	{
		add_char_to_current_screen_buffer(c, color);
		newline_on_console();
		return;
	}
	if (c == '\b')
	{
		delete_on_screen(terminal.current_screen);
		delete_on_console();
		return;
	}
	if (c == '\t')
	{
		add_char_to_current_screen_buffer(c, color);
		tab_on_console();
		return;
	}
	
	add_char_to_current_screen_buffer(c, color);
	
	terminal.vidptr[terminal.current_loc++] = c;
	terminal.vidptr[terminal.current_loc++] = color;

	fb_move_cursor(terminal.current_loc / 2);
}

/**
 * Print a string on the console
 *
 * @param str string to display
 * @param color color of the str to display
 * @return void
 */
void print_on_console(char *str, int color)
{
	unsigned int i = 0;

	/* this loop writes the string to video memory */
	while(str[i] != '\0')
		print_char_on_console(str[i++], color);
}
