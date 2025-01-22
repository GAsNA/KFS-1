#include "kernel.h"

/**
 * Add a char to choose screen buffer
 *
 * @param c character to add to buffer
 * @param color color to apply on the char
 * @param nb_screen screen to which to add to buffer
 * @return void
 */
void add_char_to_screen_buffer(char c, int color, int nb_screen)
{
	terminal.screens[nb_screen]
		.buffer[terminal.screens[nb_screen].current_loc++] = c;
	terminal.screens[nb_screen]
		.buffer[terminal.screens[nb_screen].current_loc++] = color;
}

/**
 * Add a str to choose screen buffer
 *
 * @param str string to add to buffer
 * @param color color to apply on the str
 * @param nb_screen screen to which to add to buffer
 * @return void
 */
void add_str_to_screen_buffer(char *str, int color, int nb_screen)
{
	int i = 0;
	while (str[i] != '\0')
		add_char_to_screen_buffer(str[i++], color, nb_screen);
}

/**
 * Add a char to current screen buffer
 *
 * @param c character to add to buffer
 * @param color color to apply on the char
 * @return void
 */
void add_char_to_current_screen_buffer(char c, int color)
{
	add_char_to_screen_buffer(c, color, terminal.current_screen);
}

/**
 * Add a str to current screen buffer
 *
 * @param str string to add to buffer
 * @param color color to apply on the str
 * @return void
 */
void add_str_to_current_screen_buffer(char *str, int color)
{
	add_str_to_screen_buffer(str, color, terminal.current_screen);
}


// TODO SIMILAR CODE TO PRINT_CHAR_ON_CONSOLE
static void copy_buffer_screen_to_console(int screen_number)
{
	unsigned int i = 0;
	while(i < SCREENSIZE && terminal.screens[screen_number].buffer[i] != '\0')
	{
		char c = terminal.screens[screen_number].buffer[i++];
		int color = terminal.screens[screen_number].buffer[i++];
		if (c == '\n')
			newline_on_console();
		else if (c == '\t')
			tab_on_console();
		else
		{
			terminal.vidptr[terminal.current_loc++] = c;
			terminal.vidptr[terminal.current_loc++] = color;
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

	clear_console();
	
	terminal.current_loc = 0;
	terminal.current_screen = screen_number;

	//memcpy(terminal.vidptr, terminal.screens[screen_number].buffer, SCREENSIZE);
	copy_buffer_screen_to_console(screen_number);

	fb_move_cursor(terminal.current_loc / 2);
	
	//write("SCREEN N.", 9, MAGENTA);
	//write(ft_itoa(screen_number), 1, MAGENTA);
	//write("\n", 1, MAGENTA);
}

/**
 * Delete a char on a screen ('\b')
 *
 * @param nb_screen number of the screen
 * @return void
 */
void delete_on_screen(int nb_screen)
{
	if (terminal.screens[nb_screen].current_loc - 2 >= 0)
	{
		terminal.screens[nb_screen].buffer[terminal.screens[nb_screen].current_loc - 2] = '\0';
		terminal.screens[nb_screen].current_loc -= 2;	
	}
}
