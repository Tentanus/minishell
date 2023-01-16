/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 17:21:39 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:26:22 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** The strrchr() function locates the last occurrence of c (converted to a char)
** in the string pointed to by s.  The terminating null character is considered
** to be part of the string; therefore if c is `\0', the functions locate
** the terminating `\0'.
*/

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	count;
	int	len_s;

	count = 0;
	len_s = ft_strlen(s);
	i = len_s;
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			count = i;
			i = 0;
			while (i < len_s && i < count)
			{
				i++;
				s++;
			}
			return ((char *)s);
		}
		i--;
	}
	return (NULL);
}
