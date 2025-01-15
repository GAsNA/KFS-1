#include "kernel.h"

void printk(const char *fmt, ...)
{
	print_on_console(fmt, YELLOW);
}
