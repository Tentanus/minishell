/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 10:20:49 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:26:12 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** The strlcat() copies and concatenates strings.
** Strlcat() takes the full size of the destination buffer and guarantees
** NUL-termination if there is room. Note that room for the NUL should be
** included in dstsize. strlcat() appends string src to the end of dst.
** It will append at most dstsize - strlen(dst) - 1 characters.
** It will then NUL-terminate, unless dstsize is 0 or the original dst string
** was longer than dstsize (in practice this should not happen as it means
** that either dstsize is incorrect or that dst is not a proper string).
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	len_src;
	size_t	len_dst;

	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	j = 0;
	if (dstsize > len_dst)
	{
		while (src[j] != '\0' && j < dstsize - len_dst - 1)
		{
			dst[len_dst + j] = src[j];
			j++;
		}
		dst[len_dst + j] = '\0';
		return (len_dst + len_src);
	}
	return (dstsize + len_src);
}
