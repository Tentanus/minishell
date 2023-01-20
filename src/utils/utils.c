/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:04:42 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/01/20 14:04:43 by mverbrug      ########   odam.nl         */
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
