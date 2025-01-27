#include "kernel.h"

/**
 * Initialize the main terminal
 *
 * @return void
 */
void init_terminal(void)
{
	terminal.vidptr = (char*)BEGIN_VGA;
	terminal.cursor = 0;
	
	terminal.current_screen = 0;
	
	int i = 0;
	while (i++ < LIMIT_NB_SCREENS)
		terminal.screens[i] = init_screen();

	terminal.shift = 0;
	terminal.capslock = 0;
	terminal.numslock = 1;
	terminal.to_escape = 0;
}

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
 * Add a newline on the terminal ('\n'). Is actually moving the cursor
 *
 * @return void
 */
void newline_on_terminal(void)
{
	unsigned int line_size = BYTES_FOR_ELEMENT * NB_COLUMNS;

	move_cursor(terminal.cursor + (line_size - terminal.cursor % line_size));
}

/**
 * Delete a char on the terminal ('\b')
 *
 * @return void
 */
void delete_on_terminal(void)
{
	char c = char_at_pos_in_screen(terminal.screens[terminal.current_screen].cursor - BYTES_FOR_ELEMENT, terminal.current_screen);

	if (c == '\n')
	{
		int i = BYTES_FOR_ELEMENT;
		while (terminal.vidptr[terminal.cursor - i] == '\0')
			i += BYTES_FOR_ELEMENT;
		move_cursor(terminal.cursor - i + BYTES_FOR_ELEMENT);
		// TODO if several \n in a row, skip them all: don't, stop to the previous \n
	}
	else if (c == '\t')
		move_cursor(terminal.cursor - (TAB_SIZE * BYTES_FOR_ELEMENT));
	else
	{
		if (terminal.cursor - BYTES_FOR_ELEMENT >= 0)
		{
			terminal.vidptr[terminal.cursor - BYTES_FOR_ELEMENT] = '\0';
			move_cursor(terminal.cursor - BYTES_FOR_ELEMENT);
			//move_buffer_terminal_to_left();
		}
	}
}

/**
 * Add a tab on the terminal ('\t'). Is actually moving the cursor
 *
 * @return void
 */
void tab_on_terminal(void)
{
	move_cursor(terminal.cursor + TAB_SIZE * BYTES_FOR_ELEMENT);
}

/**
 * Move the buffer to the left of one char on deletion of a char
 *
 * @return void
 */
void move_buffer_terminal_to_left(void)
{
	int i = terminal.cursor;

	while (terminal.vidptr[i + BYTES_FOR_ELEMENT] != '\0')
	{
		terminal.vidptr[i] = terminal.vidptr[i + 2];
		terminal.vidptr[i + 1] = terminal.vidptr[i + 3];
		i += BYTES_FOR_ELEMENT;
	}
	terminal.vidptr[i] = '\0';
	terminal.vidptr[i + 1] = '\0';
}

/**
 * Print a char on the terminal
 *
 * @param c char to display
 * @param color color of the char to display
 * @return void
 */
// TODO BECOME PRINT
void print_char_on_terminal(char c, int color)
{
	if (c == '\b')
	{
		delete_on_terminal();
		delete_on_screen(terminal.current_screen);
		
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

	terminal.vidptr[terminal.cursor] = c;
	terminal.vidptr[terminal.cursor + 1] = color;

	move_cursor(terminal.cursor + BYTES_FOR_ELEMENT);
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
