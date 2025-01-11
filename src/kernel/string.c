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
