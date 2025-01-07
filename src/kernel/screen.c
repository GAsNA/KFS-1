#include "kernel.h"

void blank_screen(void)
{
	unsigned int i = 0;

	/* this loops clears the screen
	 * there are 25 lines each of 80 columns;
	 * each element takes 2 bytes */
	while(i < SCREENSIZE) {
		/* blank character */
		terminal.vidptr[i++] = ' ';
		/* attribute-byte - light grey on black screen */
		terminal.vidptr[i++] = LIGHT_GRAY; 		
	}
}

void newline_on_screen(void)
{
	unsigned int line_size = BYTES_FOR_ELEMENT * NB_COLUMNS;
	terminal.current_loc += line_size - terminal.current_loc % line_size;
}

void printk_char(char c, int color)
{
	/* the character's ascii */
	terminal.vidptr[terminal.current_loc++] = c;
	/* attribute-byte: give character black bg and light grey fg */
	terminal.vidptr[terminal.current_loc++] = color;
}

void printk(char *str, int color)
{
	unsigned int i = 0;

	/* this loop writes the string to video memory */
	while(str[i] != '\0')
		printk_char(str[i++], color);
}

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
