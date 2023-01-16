/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 16:10:39 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:29:08 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** The strdup() function allocates sufficient memory for a copy of the
** string s1, does the copy, and returns a pointer to it.  The pointer may
** subsequently be used as an argument to the function free().
*/

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		len;

	len = ft_strlen(s1) + 1;
	dst = (char *)malloc(len * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, len);
	return (dst);
}
