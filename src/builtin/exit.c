/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:27:04 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/11 15:04:00 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** exit
**
*/

int	builtin_exit(t_cmd *cmd)
{
	ft_putstr_fd("exit\n", 2);
	if (cmd->args[1] != NULL)
	{
		if (cmd->args[2] == NULL)
		{
			if (ft_stris(cmd->args[1], ft_isdigit) == 1)
				return (clear_history(), exit(ft_atoi(cmd->args[1])), SUCCESS);
			if (ft_stris(cmd->args[1], ft_isdigit) == 0)
				return (mini_error(error_print, \
					1, "exit: numeric argument required"), exit(255), ERROR);
		}
		if (ft_stris(cmd->args[1], ft_isdigit) == 1)
			return (mini_error(error_print, 1, \
				"exit: too many arguments"), ERROR);
		if (ft_stris(cmd->args[1], ft_isdigit) == 0)
			return (mini_error(error_print, \
				1, "exit: numeric argument required"), exit(255), ERROR);
	}
	clear_history();
	return (exit(ft_atoi(g_status)), SUCCESS);
}

int	builtin_exit_child(t_cmd *cmd)
{
	if (cmd->args[1] != NULL)
	{
		if (cmd->args[2] == NULL)
		{
			if (ft_stris(cmd->args[1], ft_isdigit) == 1)
				return (clear_history(), _exit(ft_atoi(cmd->args[1])), SUCCESS);
			if (ft_stris(cmd->args[1], ft_isdigit) == 0)
				return (mini_error(error_print, \
					1, "exit: numeric argument required"), _exit(255), ERROR);
		}
		if (ft_stris(cmd->args[1], ft_isdigit) == 1)
			return (mini_error(error_print, 1, \
				"exit: too many arguments"), ERROR);
		if (ft_stris(cmd->args[1], ft_isdigit) == 0)
			return (mini_error(error_print, \
				1, "exit: numeric argument required"), _exit(255), ERROR);
	}
	clear_history();
	return (_exit(ft_atoi(g_status)), SUCCESS);
}
