/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 11:44:35 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:29:20 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Applies the function ’f’ to each character of the string ’s’ to create a
** new string (with malloc(3)) resulting from successive applications of ’f’.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	len;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
