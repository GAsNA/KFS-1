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
	char c = char_at_pos_in_screen(terminal.screens[terminal.current_screen].cursor - 2, terminal.current_screen);

	if (c == '\n')
	{
		int i = 0;
		while (terminal.vidptr[terminal.cursor - i] == '\0')
			i += 2;
		move_cursor(terminal.cursor - i + 2);
	}
	else if (c == '\t')
	{
		int i = 0;
		while (i < TAB_SIZE * 2)
			i += 2;
		move_cursor(terminal.cursor - (TAB_SIZE * 2));
	}
	else
	{
		if (terminal.cursor - 2 >= 0)
		{
			terminal.vidptr[terminal.cursor - 2] = '\0';
			move_cursor(terminal.cursor - 2);
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
	move_cursor(terminal.cursor + TAB_SIZE * 2);
}

/**
 * Move the buffer to the left of one char on deletion of a char
 *
 * @return void
 */
void move_buffer_terminal_to_left(void)
{
	int i = terminal.cursor;

	while (terminal.vidptr[i + 2] != '\0')
	{
		terminal.vidptr[i] = terminal.vidptr[i + 2];
		terminal.vidptr[i + 1] = terminal.vidptr[i + 3];
		i += 2;
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
void print_char_on_terminal(char c, int color)
{
	if (c == '\b')
	{
		delete_on_terminal(); // if on screen is \n so go to next char, if is \t go TAB_SIZE in back
		// Verify the same thing when moving cursor left or right, BUT how to move up and down
		// -> for up and down, maybe solution is to not do and begin to work on a term like presentation
		// rename (and move) this function to 'print' or something like that and seperate functions for print only on term and screen
		delete_on_screen(terminal.current_screen); // Delete on screen after delete on term
		
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

	move_cursor(terminal.cursor + 2);
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
