#include "kernel.h"

/**
 * Print the arguments given for printk
 *
 * @param c the character that represents the type of value to display
 * @param color the color to use to print
 * @return void
 */
static void print_arg(char c, void **arg, int color)
{
	if (c == 'c')
		print_char_on_terminal((char)*(char *)(arg), color);
	else if (c == 's')
		print_on_terminal(*(char **)(arg), color);
	else if (c == 'p')
		putaddr((unsigned int)*(char **)(arg), color);
	else if (c == 'i' || c == 'd')
		print_on_terminal(itoa((int)*(int **)(arg)), color);
	else if (c == 'u')
		print_on_terminal(itoa((unsigned int)*(int **)(arg)), color);
	else if (c == 'x')
		puthexa_small((int)*(int **)(arg), color);
	else if (c == 'X')
		puthexa_capital((int)*(int **)(arg), color);
	else if (c == '%')
		print_char_on_terminal('%', color);
}

/**
 * Print messages with a log level to the kernel
 *
 * @param fmt format string to print
 * @return void
 */
void printk(char *fmt, ...)
{
	int i = 0;
	int color = LIGHT_GRAY;
	void **args = (void **) &fmt;
	args++;

	if (!fmt)
		return;

	// Print the header and choose color
	if (strncmp(fmt, KERN_EMERG, 3) == 0)
	{
		color = RED;
		print_on_terminal("<emerg> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_ALERT, 3) == 0)
	{
		color = RED;
		print_on_terminal("<alert> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_CRIT, 3) == 0)
	{
		color = RED;
		print_on_terminal("<crit> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_ERR, 3) == 0)
	{
		color = RED;
		print_on_terminal("<err> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_WARNING, 3) == 0)
	{
		color = YELLOW;
		print_on_terminal("<warn> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_NOTICE, 3) == 0)
	{
		color = MAGENTA;
		print_on_terminal("<notice> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_INFO, 3) == 0)
	{
		color = LIGHT_GRAY;
		print_on_terminal("<info> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_DEBUG, 3) == 0)
	{
		color = LIGHT_GRAY;
		print_on_terminal("<debug> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_CONT, 3) == 0)
	{
		color = LIGHT_GRAY;
		print_on_terminal("<cont> ", color);
		fmt = fmt + 3;
	}
	else
	{
		color = LIGHT_GRAY;
		print_on_terminal("<default> ", color);
	}
	
	// Interpret the string
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			print_arg(fmt[i], args, color);
			args++;
		}
		else
			print_char_on_terminal(fmt[i], color);
		i++;
	}
}
