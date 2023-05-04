/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:05:05 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/04 17:12:16 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	builtin_check(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	return (false);
}

int	builtin_execute(t_cmd *cmd, t_env_var_ll **env_var_list)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (builtin_echo(cmd, 1)); // right fd?
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (builtin_pwd(1)); // right fd?
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (builtin_cd(cmd, env_var_list));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (builtin_env(*env_var_list));
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (builtin_unset(cmd, env_var_list));
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (builtin_export(cmd, env_var_list));
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (builtin_exit(cmd));
	return (ERROR);
}

int	handle_builtin(t_cmd *cmd, t_minishell *mini)
{
	if (builtin_check(cmd->args[0]) == true)
	{
		handle_redirect(cmd->redir, redir_error);
		if (builtin_execute(cmd, &mini->env_list) == SUCCESS)
			return (status_update(0), SUCCESS);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
