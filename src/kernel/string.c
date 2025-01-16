#include "kernel.h"

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

/**
 * Copy n bytes from src memory to dest memory
 *
 * @param dest memory to which the bytes are copied
 * @param src memory from which the bytes are copied
 * @param n number of bytes to copy
 * @return pointer to dest memory
 */
void *memcpy(void *dest, const void *src, int n)
{
	int i;

	if (!dest && !src)
		return 0;

	i = -1;
	while (++i < n)
		((unsigned char *) dest)[i] = ((unsigned char *) src)[i];

	return dest;
}

/**
 * Compare n bytes from two strings
 *
 * @param s1 first string to compare
 * @param s2 second string to compare
 * @param n the number of bytes to compare
 * @return the difference between the first different characters
 */
int strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void display_str(const char *str, va_list args)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			display_arg(str, i, args);
		}
		else
			//putchar(str[i]);
		i++;
	}
}

static void display_arg(const char *str, int i, va_list args)
{
	if (str[i] == 'c')
		putchar(va_arg(args, int));
	else if (str[i] == 's')
		putstr(va_arg(args, char *));
	else if (str[i] == 'p')
		putaddr((size_t)va_arg(args, char *));
	else if (str[i] == 'i' || s[i] == 'd')
		putnbr(va_arg(args, int));
	else if (str[i] == 'u')
		putnbru((unsigned int)va_arg(args, int));
	else if (str[i] == 'x')
		puthexa(va_arg(args, int), "0123456789abcdef");
	else if (str[i] == 'X')
		puthexa(va_arg(args, int), "0123456789ABCDEF");
	else if (str[i] == '%')
		putchar('%');
}

/**
 * Print an interpreted string
 *
 * @param str string to interpret with other args
 * @return the number of charater printed
 */
void printf(const char *str, ...)
{
	va_list	args;
	int count;

	va_start(args, str);
	display_str(str, args);
	va_end(args);
}


