#include "kernel.h"

void printk(char *fmt, ...)
{
	int color = LIGHT_GRAY;
	void **args = (void **) &fmt;

	args++;

	if (!fmt)
		return;
/*
	if (strncmp(fmt, KERN_EMERG, 3) == 0)
	{
		color = RED;
		printf("<emerg> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_ALERT, 3) == 0)
	{
		color = RED;
		printf("<alert> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_CRIT, 3) == 0)
	{
		color = RED;
		printf("<crit> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_ERR, 3) == 0)
	{
		color = RED;
		printf("<err> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_WARNING, 3) == 0)
	{
		color = YELLOW;
		printf("<warn> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_NOTICE, 3) == 0)
	{
		color = MAGENTA;
		printf("<notice> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_INFO, 3) == 0)
	{
		color = LIGHT_GRAY;
		printf("<info> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_DEBUG, 3) == 0)
	{
		color = LIGHT_GRAY;
		printf("<debug> ", color);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_CONT, 3) == 0)
	{
		color = LIGHT_GRAY;
		printf("<cont> ", color);
		fmt = fmt + 3;
	}
	else
	{
		color = LIGHT_GRAY;
		printf("<default> ", color);
	}
*/
	//print_on_console(*(char **)(args), color);
	printf(fmt, color, *args);
}
