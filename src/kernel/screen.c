#include "kernel.h"

static void write(char *str, int limit, int color);

/**
 * Add a char to choose screen buffer
 *
 * @param c character to add to buffer
 * @param screen screen to which to add to buffer
 * @return void
 */
void add_char_to_screen_buffer(char c, int nb_screen)
{
	terminal.screens[nb_screen]
		.buffer[terminal.screens[nb_screen].current_loc++] = c;
}

/**
 * Add a str to choose screen buffer
 *
 * @param str string to add to buffer
 * @param screen screen to which to add to buffer
 * @return void
 */
void add_str_to_screen_buffer(char *str, int nb_screen)
{
	int i = 0;
	while (str[i] != '\0')
		add_char_to_screen_buffer(str[i++], nb_screen);
}

/**
 * Add a char to current screen buffer
 *
 * @param c character to add to buffer
 * @return void
 */
void add_char_to_current_screen_buffer(char c)
{
	add_char_to_screen_buffer(c, terminal.current_screen);
}

/**
 * Add a str to current screen buffer
 *
 * @param str string to add to buffer
 * @return void
 */
void add_str_to_current_screen_buffer(char *str)
{
	add_str_to_screen_buffer(str, terminal.current_screen);
}

static void write(char *str, int limit, int color)
{
	unsigned int i = 0;
	while(i < limit)
	{
		char c = str[i];
		if (c == '\n')
			newline_on_console();
		else if (c == '\b')
			delete_on_console();		// TODO: char /b should not be on buffer
		else if (c == '\t')
			tab_on_console();
		else
		{
			terminal.vidptr[terminal.current_loc++] = c;
			terminal.vidptr[terminal.current_loc++] = color;
		}
		i++;
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
	
	char *str = terminal.screens[screen_number].buffer;
	int limit = terminal.screens[screen_number].current_loc;
	write(str, limit, LIGHT_GRAY);

	write("SCREEN N.", 9, MAGENTA);
	write(ft_itoa(screen_number), 1, MAGENTA);
	write("\n", 1, MAGENTA);
}
