#include "kernel.h"

void add_to_console_buffer(char c, int color)
{
	terminal.screens[terminal.current_screen]
		.buffer[terminal.screens[terminal.current_screen].current_loc++] = c;
	terminal.screens[terminal.current_screen]
		.buffer[terminal.screens[terminal.current_screen].current_loc++] = color;

	terminal.vidptr[terminal.current_loc++] = c;
	terminal.vidptr[terminal.current_loc++] = color;
}

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
	while(i < SCREENSIZE) {
		terminal.vidptr[i++] = ' ';
		terminal.vidptr[i++] = LIGHT_GRAY; 		
	}
}

/**
 * Return add a newline on the console ('\n')
 *
 * @return void
 */
void newline_on_console(void)
{
	unsigned int line_size = BYTES_FOR_ELEMENT * NB_COLUMNS;
	terminal.current_loc += line_size - terminal.current_loc % line_size;
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
	if (c == '\n')
	{
		newline_on_console();
		return;
	}
	if (c == '\b')
	{
		if (terminal.current_loc - 2 >= 0)
		{
			terminal.vidptr[terminal.current_loc - 2] = '\0';
			terminal.current_loc -= 2;
		}
		return;
	}
	if (c == '\t')
	{
		int i = 0;
		while (i++ < TAB_SIZE)
			printk_char(' ', color);
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

/**
 * Calcul the number of digits in a number
 *
 * @param n the number
 * @return number of digits
 */
static int nbrlen(int n)
{
	long	nb = n;
	int	len = 0;

	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

/**
 * Transform an int to a string
 *
 * @param n the number to transform
 * @return the string of the number
 */
char *ft_itoa(int n)
{
	long	nb = n;
	int	len = nbrlen(nb), i;
	static char	str[5];

	if (!str)
		return (0);
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	i = len;
	while (nb > 0)
	{
		str[--i] = (nb % 10) + '0';
		nb /= 10;
	}
	str[len] = '\0';
	return (str);
}
