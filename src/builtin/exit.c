/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:27:04 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/16 11:26:42 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** exit
**
*/

bool str_is_number(char *str)
{
	int i;
	
	i = 0;
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-')
		i++;
	else
		return (false);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

int	str_to_exit_code(char *str)
{
	int	exit_code;

	exit_code = ft_atoi(str);
	if (exit_code > 255 || exit_code < -255)
		return (exit_code % 255);
	return (exit_code);
}


int	builtin_exit(t_cmd *cmd)
{
	int exit_code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->args[1] != NULL)
	{
		if (cmd->args[2] == NULL)
		{
			if (str_is_number(cmd->args[1]) == true)
			{
				exit_code = str_to_exit_code(cmd->args[1]);
				return (clear_history(), exit(exit_code), SUCCESS);
			}
			if (str_is_number(cmd->args[1]) == false)
				return (mini_error(error_print, \
					1, "exit: numeric argument required"), exit(255), ERROR);
		}
		if (str_is_number(cmd->args[1]) == true)
			return (mini_error(error_print, 1, \
				"exit: too many arguments"), ERROR);
		if (str_is_number(cmd->args[1]) == false)
			return (mini_error(error_print, \
				1, "exit: numeric argument required"), exit(255), ERROR);
	}
	clear_history();
	return (exit(ft_atoi(g_status)), SUCCESS);
}

int	builtin_exit_child(t_cmd *cmd)
{
	int exit_code;
	
	if (cmd->args[1] != NULL)
	{
		if (cmd->args[2] == NULL)
		{
			if (str_is_number(cmd->args[1]) == true)
			{
				exit_code = str_to_exit_code(cmd->args[1]);
				return (clear_history(), _exit(exit_code), SUCCESS);
			}
			if (str_is_number(cmd->args[1]) == false)
				return (mini_error(error_print, \
					1, "exit: numeric argument required"), _exit(255), ERROR);
		}
		if (str_is_number(cmd->args[1]) == true)
			return (mini_error(error_print, 1, \
				"exit: too many arguments"), ERROR);
		if (str_is_number(cmd->args[1]) == false)
			return (mini_error(error_print, \
				1, "exit: numeric argument required"), _exit(255), ERROR);
	}
	clear_history();
	return (_exit(ft_atoi(g_status)), SUCCESS);
}
