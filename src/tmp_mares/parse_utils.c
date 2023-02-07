/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:04:42 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/02/07 12:10:37 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_double_array(char **double_array)
{
	int	i;

	i = 0;
	while (double_array[i] != NULL)
	{
		free(double_array[i]);
		// double_array[i] = NULL;
		i++;
	}
	free(double_array);
	// double_array = NULL;
	return ;
}

char	**make_double_array(int word_count)
{
	char	**result;
	int		i;

	i = 0;
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < word_count)
	{
		result[i] = (char *)malloc(1024 * sizeof(char));
		if (!result[i])
			return (NULL);
		i++;
	}
	// result[i] = (char *)malloc(1024 * sizeof(char *));
	// if (!result[i])
	// 	return (NULL);
	// result[i] = NULL;
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
