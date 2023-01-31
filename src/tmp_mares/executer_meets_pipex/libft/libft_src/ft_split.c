/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:57:01 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/10/06 15:32:22 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Allocates (with malloc) and returns an array of strings obtained by
** splitting ’s’ using the character ’c’ as a delimiter. The array must be
** ended by a NULL pointer.
*/

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

char	**ft_make_array(int word_count)
{
	char	**result;

	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

char	**ft_free(char **result, size_t word_index)
{
	size_t	i;

	i = 0;
	while (i < word_index)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

size_t	ft_size_word(char const *s, char c)
{
	size_t	i;
	size_t	word_size;
	size_t	len_s;

	i = 0;
	word_size = 0;
	len_s = ft_strlen(s);
	while (i < len_s && s[i] != c)
	{
		word_size++;
		i++;
	}
	return (word_size);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		word_index;

	if (!s)
		return (NULL);
	word_count = ft_word_counter(s, c);
	result = ft_make_array(word_count);
	if (!result)
		return (NULL);
	word_index = 0;
	while (word_count > 0)
	{
		while (*s && *s == c)
			s++;
		result[word_index] = ft_substr(s, 0, ft_size_word(s, c));
		if (!result[word_index])
			return (ft_free(result, word_index));
		s = s + ft_size_word(s, c);
		word_index++;
		word_count--;
	}
	result[word_index] = NULL;
	return (result);
}
