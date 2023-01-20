/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 10:25:07 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:29:12 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Allocates (with malloc(3)) and returns a new string, which is the result
** of the concatenation of ’s1’ and ’s2’.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined = malloc(len_s1 + len_s2 + 1);
	if (!joined)
		return (NULL);
	ft_memmove(joined, s1, len_s1);
	i = 0;
	while (i < len_s2)
	{
		joined[len_s1 + i] = s2[i];
		i++;
	}
	joined[len_s1 + len_s2] = '\0';
	return (joined);
}
