#include "kernel.h"
#include <stddef.h>
#include <stdarg.h>

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
char *itoa(int n)
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

/**
 * Print a memory address in hexa
 *
 * @param num the value to which the address belongs
 * @param color the color to use to print
 * @return void
 */
void putaddr(int num, int color)
{
	char str[255];
	int i;

	if (!num)
		return (print_on_console("0x0", color));
	i = 0;
	while (num > 0)
	{
		str[i] = ("0123456789abcdef"[num % 16]);
		num = num / 16;
		i++;
	}
	print_on_console("0x", color);
	i--;
	while (i >= 0)
	{
		print_char_on_console(str[i], color);
		i--;
	}
}

/**
 * Print a value in hexa in small characters
 *
 * @param nb the value to convert and print
 * @param color the color to use to print
 * @return void
 */
void puthexa_small(int nb, int color)
{
	char *hexa = "0123456789abcdef";
	long	n;

	n = nb;
	if (n < 0)
		n += 4294967296;
	if (n >= 16)
	{
		puthexa_small(n / 16, color);
		print_char_on_console(hexa[n % 16], color);
	}
	else
		print_char_on_console(hexa[n], color);
}

/**
 * Print a value in hexa in capital characters
 *
 * @param nb the value to convert and print
 * @param color the color to use to print
 * @return void
 */
void puthexa_capital(int nb, int color)
{
	char *hexa = "0123456789ABCDEF";
	long	n;

	n = nb;
	if (n < 0)
		n += 4294967296;
	if (n >= 16)
	{
		puthexa_capital(n / 16, color);
		print_char_on_console(hexa[n % 16], color);
	}
	else
		print_char_on_console(hexa[n], color);
}
