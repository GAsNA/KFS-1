#include "kernel.h"

void printk(const char *fmt, ...)
{
	if (!fmt)
		return;

	if (strncmp(fmt, KERN_EMERG, 3) == 0)
		pr_emerg(fmt);
	else if (strncmp(fmt, KERN_ALERT, 3) == 0)
		pr_alert(fmt);
	else if (strncmp(fmt, KERN_CRIT, 3) == 0)
		pr_crit(fmt);
	else if (strncmp(fmt, KERN_ERR, 3) == 0)
		pr_err(fmt);
	else if (strncmp(fmt, KERN_WARNING, 3) == 0)
		pr_warn(fmt);
	else if (strncmp(fmt, KERN_NOTICE, 3) == 0)
		pr_notice(fmt);
	else if (strncmp(fmt, KERN_INFO, 3) == 0)
		pr_info(fmt);
	else if (strncmp(fmt, KERN_DEBUG, 3) == 0)
		pr_debug(fmt);
	else if (strncmp(fmt, KERN_CONT, 3) == 0)
		pr_cont(fmt);
	else
		pr_default(fmt);
}
