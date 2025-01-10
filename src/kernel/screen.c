#include "kernel.h"

/**
 * Add a char to current screen buffer
 *
 * @param c character to add to buffer
 * @return void
 */
void add_to_current_screen_buffer(char c)
{
	t_screen	*screen = &terminal.screens[terminal.current_screen];

	screen->buffer[screen->current_loc++] = c;
}

static void write(char *str, int limit, int color)
{
	unsigned int i = 0;
	while(i < limit)
	{
		char c = str[i];
		if (c == '\n')
			newline_on_console();
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
	
	terminal.vidptr = (char *)BEGIN_VGA;
	terminal.current_loc = 0;
	terminal.current_screen = screen_number;
	
	char *str = terminal.screens[screen_number].buffer;
	int limit = terminal.screens[screen_number].current_loc;
	write(str, limit, LIGHT_GRAY);

	write("SCREEN N.", 9, MAGENTA);
	write(ft_itoa(screen_number), 1, MAGENTA);
	write("\n", 1, MAGENTA);
}
