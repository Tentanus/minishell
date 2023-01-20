/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:32:31 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/10/06 16:35:57 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*
	handle_execve1_fail() ensures right exit codes and messages
    when execve for cmd1 is not successfull.
*/

void	handle_execve1_fail(t_args *arg, char **argv)
{
	if (checks(argv) == 1)
		cmd_not_found("command not found:", 0, "");
	if (checks(argv) == 2)
		cmd_not_found("permission denied:", 0, "");
	if (access(*arg->cmd1_split, X_OK) != 0 && arg->cmd1_split[0][0] != '/')
		cmd_not_found("command not found: ", 0, arg->cmd1_split[0]);
	double_error_message(errno, arg->cmd1_split[0]);
}

/*
	str_is_space checks of which characters the string exists.
	Returns 0 if string exists of whitespace.
	Returns 1 if string exists of not-whitespace-characters.
	Returns 2 if string does not exist.
*/

int	str_is_space(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (2);
	while (str[i])
	{
		if (str[i] != '\t' && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

/*
	Get_cmd splits cmd on space and checks for sed.
	If cmd = sed, options are checked and ' is trimmed off of script.
*/

char	**check_sed(char **input_split, int word_count)
{
	if (ft_strncmp(input_split[0], "sed", 3) == 0)
	{
		if (input_split[2] == NULL)
		{
			input_split[1] = ft_strtrim(input_split[1], "\'");
			if (!input_split[1])
				exit(127);
		}
		else
		{
			input_split[word_count - 1]
				= ft_strtrim(input_split[word_count - 1], "\'");
			if (!input_split[word_count - 1])
				exit(127);
		}
	}
	return (input_split);
}

char	**free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}
