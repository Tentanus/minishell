/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 13:24:57 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:29:27 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Allocates (with malloc) and returns a copy of ’s1’ with the characters
** specified in ’set’ removed from the beginning and the end of the string.
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	while (s1[0] && ft_strchr(set, s1[0]))
		s1++;
	end = ft_strlen(s1);
	while (s1[0] && ft_strchr(set, s1[end - 1]))
		end--;
	trimmed = ft_substr(s1, 0, end);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
