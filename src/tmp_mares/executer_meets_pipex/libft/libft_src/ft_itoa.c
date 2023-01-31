/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 15:22:22 by mverbrug      #+#    #+#                 */
/*   Updated: 2021/04/06 14:57:05 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** Allocates (with malloc) and returns a string representing the integer
** received as an argument. Negative numbers must be handled.
*/

static int	ft_digit_counter(int n)
{
	int		count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		count;
	int		minus;

	count = ft_digit_counter(n);
	if (n < 0)
		minus = 1;
	else
		minus = 0;
	result = (char *)malloc((count + 1 + minus) * sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	result[count + minus] = '\0';
	while (count)
	{
		result[count + minus - 1] = ft_abs(n % 10) + '0';
		n /= 10;
		count--;
	}
	return (result);
}
