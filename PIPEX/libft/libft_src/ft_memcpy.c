/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 12:36:33 by mverbrug      #+#    #+#                 */
/*   Updated: 2021/04/06 14:57:57 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** The memcpy() function copies n bytes from memory area src to memory area dst.
** If dstand src overlap, behavior is undefined.  Applications in which dst
** and src might overlap should use memmove() instead.
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
