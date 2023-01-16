/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/08 19:02:56 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:26:31 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** The strnstr() function locates the first occurrence of the null-terminated
** string needle in the string haystack, where not more than len characters are
** searched. Characters that appear after a `\0' character are not searched.
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_haystack;
	size_t	len_needle;

	i = 0;
	len_haystack = ft_strlen(haystack);
	len_needle = ft_strlen(needle);
	if (len_needle == 0)
		return ((char *)haystack);
	else
	{
		while (haystack[i] != '\0' && i < len
			&& i <= (len_haystack - len_needle))
		{
			if (needle[0] == haystack[i])
			{
				if (ft_strncmp(&haystack[i], needle, len_needle) == 0
					&& len >= i + len_needle)
					return ((char *)&haystack[i]);
			}
			i++;
		}
		return (NULL);
	}
}
