#include "kernel.h"

/**
 * Initialize a screen and return it
 *
 * @return an initialized screen
 */
t_screen init_screen(void)
{
	t_screen screen;

	screen.buffer[0] = '\0';
	screen.current_loc = 0;
	
	return screen;
}

/**
 * Add a char to choose screen buffer
 *
 * @param c character to add to buffer
 * @param colour colour to apply on the char
 * @param nb_screen screen to which to add to buffer
 * @return void
 */
void add_char_to_screen_buffer(char c, int colour, int nb_screen)
{
	terminal.screens[nb_screen]
		.buffer[terminal.screens[nb_screen].current_loc++] = c;
	terminal.screens[nb_screen]
		.buffer[terminal.screens[nb_screen].current_loc++] = colour;
}

/**
 * Add a str to choose screen buffer
 *
 * @param str string to add to buffer
 * @param colour colour to apply on the str
 * @param nb_screen screen to which to add to buffer
 * @return void
 */
void add_str_to_screen_buffer(char *str, int colour, int nb_screen)
{
	int i = 0;
	while (str[i] != '\0')
		add_char_to_screen_buffer(str[i++], colour, nb_screen);
}

/**
 * Add a char to current screen buffer
 *
 * @param c character to add to buffer
 * @param colour colour to apply on the char
 * @return void
 */
void add_char_to_current_screen_buffer(char c, int colour)
{
	add_char_to_screen_buffer(c, colour, terminal.current_screen);
}

/**
 * Add a str to current screen buffer
 *
 * @param str string to add to buffer
 * @param colour colour to apply on the str
 * @return void
 */
void add_str_to_current_screen_buffer(char *str, int colour)
{
	add_str_to_screen_buffer(str, colour, terminal.current_screen);
}


// TODO SIMILAR CODE TO PRINT_CHAR_ON_TERMINAL
static void copy_buffer_screen_to_terminal(int screen_number)
{
	unsigned int i = 0;
	while(i < SCREENSIZE && terminal.screens[screen_number].buffer[i] != '\0')
	{
		char c = terminal.screens[screen_number].buffer[i++];
		int colour = terminal.screens[screen_number].buffer[i++];
		if (c == '\n')
			newline_on_terminal();
		else if (c == '\t')
			tab_on_terminal();
		else
		{
			terminal.vidptr[terminal.current_loc++] = c;
			terminal.vidptr[terminal.current_loc++] = colour;
		}
	}
}

/**
 * Change the current visualized screen
 *
 * @param screen_number number of the screen to display
 * @return void
 */
void change_screen(int screen_number)
{
	if (screen_number < 0 || screen_number >= LIMIT_NB_SCREENS)
		return;

	clear_terminal();
	
	terminal.current_loc = 0;
	terminal.current_screen = screen_number;

	//memcpy(terminal.vidptr, terminal.screens[screen_number].buffer, SCREENSIZE);
	copy_buffer_screen_to_terminal(screen_number);

	move_cursor(terminal.current_loc / 2);
	
	//write("SCREEN N.", 9, MAGENTA);
	//write(ft_itoa(screen_number), 1, MAGENTA);
	//write("\n", 1, MAGENTA);
}

/**
 * Delete a char on a screen ('\b')
 *
 * @param screen_number number of the screen
 * @return void
 */
void delete_on_screen(int screen_number)
{
	if (terminal.screens[screen_number].current_loc - 2 >= 0)
	{
		terminal.screens[screen_number].buffer[terminal.screens[screen_number].current_loc - 2] = '\0';
		terminal.screens[screen_number].current_loc -= 2;
	}

	move_buffer_screen_to_left(screen_number);	
}

/**
 * Move the buffer to the left of one char on deletion of a char
 *
 * @param screen_number number of the screen
 * @return void
 */
void move_buffer_screen_to_left(int screen_number)
{
	int i = terminal.screens[screen_number].current_loc;

	while (terminal.screens[screen_number].buffer[i + 2] != '\0')
	{
		terminal.screens[screen_number].buffer[i] = terminal.screens[screen_number].buffer[i + 2];
		terminal.screens[screen_number].buffer[i + 1] = terminal.screens[screen_number].buffer[i + 3];
		i += 2;
	}
	terminal.screens[screen_number].buffer[i] = '\0';
}
