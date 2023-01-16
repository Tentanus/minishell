/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 13:37:24 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:25:59 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** The strlcpy() copies and concatenates strings.
** Strlcpy() takes the full size of the destination buffer and guarantees
** NUL-termination if there is room. Note that room for the NUL should be
** included in dstsize. Strlcpy() copies up to dstsize - 1 characters from
** the string src to dst, NUL-terminating the result if dstsize is not 0.
*/

size_t	ft_strlcpy(char *dst, const	char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;

	if (!src || !dst)
		return (0);
	i = 0;
	len_src = ft_strlen(src);
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		if (dstsize != 0)
			dst[i] = '\0';
	}
	return (len_src);
}
