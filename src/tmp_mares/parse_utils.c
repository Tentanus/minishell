/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:04:42 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/01/25 15:47:46 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**make_double_array(int word_count)
{
	char	**result;

	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

int	ft_word_counter(char const *s, char c)
{
	size_t	i;
	size_t	word_count;
	size_t	len_str;
	char	*str;

	word_count = 0;
	str = (char *)s;
	i = 0;
	len_str = ft_strlen(str);
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			word_count++;
		i++;
	}
	if (len_str > 0 && str[len_str - 1] != c)
		word_count++;
	return (word_count);
}
