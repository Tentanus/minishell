/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 15:27:01 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/09/26 12:47:32 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** The memset() function writes len bytes of
** value c (converted to an unsigned char) to the string b.
*/

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	s = b;
	i = 0;
	while (i < len)
	{
		s[i] = c;
		i++;
	}
	return (s);
}
