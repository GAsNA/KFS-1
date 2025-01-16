#include "kernel.h"
#include <stdarg.h>

static void pr_emerg(const char *str, va_list args)
{
	int color = RED;
	
	printf("<emerg> ", color, args);
	printf(str + 3, color, args);
}

static void pr_alert(const char *str, va_list args)
{
	int color = RED;

	printf("<alert> ", color, args);
	printf(str + 3, color, args);
}

static void pr_crit(const char *str, va_list args)
{
	int color = RED;

	printf("<crit> ", color, args);
	printf(str + 3, color, args);
}

static void pr_err(const char *str, va_list args)
{
	int color = RED;

	printf("<err> ", color, args);
	printf(str + 3, color, args);
}

static void pr_warn(const char *str, va_list args)
{
	int color = YELLOW;

	printf("<warn> ", color, args);
	printf(str + 3, color, args);
}

static void pr_notice(const char *str, va_list args)
{
	int color = MAGENTA;

	printf("<notice> ", color, args);
	printf(str + 3, color, args);
}

static void pr_info(const char *str, va_list args)
{
	int color = LIGHT_GRAY;

	printf("<info> ", color, args);
	printf(str + 3, color, args);
}

static void pr_debug(const char *str, va_list args)
{
	int color = LIGHT_GRAY;

	printf("<debug> ", color, args);
	printf(str + 3, color, args);
}

static void pr_default(const char *str, va_list args)
{
	int color = LIGHT_GRAY;

	printf("<default> ", color, args);
	printf(str + 3, color, args);
}

static void pr_cont(const char *str, va_list args)
{
	int color = LIGHT_GRAY;

	printf("<cont> ", color, args);
	printf(str + 3, color, args);
}

void printk(char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);

	if (!fmt)
		return;

	if (strncmp(fmt, KERN_EMERG, 3) == 0)
		pr_emerg(fmt, args);
	else if (strncmp(fmt, KERN_ALERT, 3) == 0)
		pr_alert(fmt, args);
	else if (strncmp(fmt, KERN_CRIT, 3) == 0)
		pr_crit(fmt, args);
	else if (strncmp(fmt, KERN_ERR, 3) == 0)
		pr_err(fmt, args);
	else if (strncmp(fmt, KERN_WARNING, 3) == 0)
		pr_warn(fmt, args);
	else if (strncmp(fmt, KERN_NOTICE, 3) == 0)
		pr_notice(fmt, args);
	else if (strncmp(fmt, KERN_INFO, 3) == 0)
		pr_info(fmt, args);
	else if (strncmp(fmt, KERN_DEBUG, 3) == 0)
		pr_debug(fmt, args);
	else if (strncmp(fmt, KERN_CONT, 3) == 0)
		pr_cont(fmt, args);
	else
		pr_default(fmt, args);

	va_end(args);
}
