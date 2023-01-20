/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/22 16:04:08 by mverbrug      #+#    #+#                 */
/*   Updated: 2021/02/08 19:02:00 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** The strchr() function locates the first occurrence of c (converted to a char)
** in the string pointed to by s.  The terminating null character is considered
** to be part of the string; therefore if c is `\0', the functions locate the
** terminating `\0'.
*/

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	new_c;

	str = (char *)s;
	new_c = c;
	while (*str)
	{
		if (*str == new_c)
			return (str);
		str++;
	}
	if (new_c == '\0' && *str == '\0')
		return (str);
	return (NULL);
}
