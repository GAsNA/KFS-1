#include "kernel.h"

/**
 * Blank the entire terminal
 *
 * @return void
 */
void clear_terminal(void)
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
 * Add a newline on the terminal ('\n')
 *
 * @return void
 */
void newline_on_terminal(void)
{
	unsigned int line_size = BYTES_FOR_ELEMENT * NB_COLUMNS;
	terminal.current_loc += line_size - terminal.current_loc % line_size;

	move_cursor(terminal.current_loc / 2);
}

/**
 * Delete a char on the terminal ('\b')
 *
 * @return void
 */
void delete_on_terminal(void)
{
	if (terminal.current_loc - 2 >= 0)
	{
		terminal.vidptr[terminal.current_loc - 2] = '\0';
		terminal.current_loc -= 2;

		move_cursor(terminal.current_loc / 2);
	}

	move_buffer_terminal_to_left();
}

/**
 * Add a tab on the terminal ('\t')
 *
 * @return void
 */
void tab_on_terminal(void)
{
	int i = 0;
	while (i++ < TAB_SIZE)
		print_char_on_terminal(' ', LIGHT_GRAY);
}

/**
 * Move the buffer to the left of one char on deletion of a char
 *
 * @return void
 */
void move_buffer_terminal_to_left(void)
{
	int i = terminal.current_loc;

	while (terminal.vidptr[i + 2] != '\0')
	{
		terminal.vidptr[i] = terminal.vidptr[i + 2];
		terminal.vidptr[i + 1] = terminal.vidptr[i + 3];
		i += 2;
	}
	terminal.vidptr[i] = '\0';
}

/**
 * Print a char on the terminal
 *
 * @param c char to display
 * @param color color of the char to display
 * @return void
 */
void print_char_on_terminal(char c, int color)
{
	if (c == '\b')
	{
		delete_on_screen(terminal.current_screen);
		delete_on_terminal();
		
		return;
	}

	add_char_to_current_screen_buffer(c, color);

	if (c == '\n')
	{
		newline_on_terminal();
		return;
	}
	if (c == '\t')
	{
		tab_on_terminal();
		return;
	}

	// TODO current_loc update dans move_cursor
	
	terminal.vidptr[terminal.current_loc++] = c;
	terminal.vidptr[terminal.current_loc++] = color;

	move_cursor(terminal.current_loc / 2);
}

/**
 * Print a string on the terminal
 *
 * @param str string to display
 * @param color color of the str to display
 * @return void
 */
void print_on_terminal(char *str, int color)
{
	unsigned int i = 0;

	/* this loop writes the string to video memory */
	while(str[i] != '\0')
		print_char_on_terminal(str[i++], color);
}
