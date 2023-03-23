/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:05:05 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/03/23 18:19:08 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	builtin_check(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0) // echo.c
		return (true);
	if (ft_strncmp(cmd, "pwd", 4) == 0) // pwd.c
		return (true);
	if (ft_strncmp(cmd, "cd", 3) == 0) // cd.c
		return (true);
	if (ft_strncmp(cmd, "env", 4) == 0) // env.c
		return (true);
	if (ft_strncmp(cmd, "unset", 6) == 0) // unset.c
        return(true);
	if (ft_strncmp(cmd, "export", 7) == 0) // export.c
		return(true);
	if (ft_strncmp(cmd, "exit", 5) == 0) // exit.c
		return(true);
	return (false);
}

void	builtin_execute(t_cmd *cmd, t_env_var_ll **env_var_list)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		builtin_echo(cmd, 1);
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		builtin_pwd(1);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		builtin_cd(cmd, env_var_list);
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		builtin_env(*env_var_list);
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
        builtin_unset(cmd->args[1], env_var_list);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		builtin_export(cmd, env_var_list);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		builtin_exit(cmd);
}
