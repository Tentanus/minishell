/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:05:05 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/02/21 14:30:02 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_builtin(char *cmd)
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
        return(true);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return(true);
	// if (ft_strncmp(cmd, "exit", 5) == 0)
	// 	return(true);
	return (false);
}

void	execute_builtin(t_cmd *cmd, t_env_var *our_env_var)
{
	if (ft_strncmp(cmd->simple_cmd, "echo", 5) == 0)
		execute_echo(cmd, 1);
	if (ft_strncmp(cmd->simple_cmd, "pwd", 4) == 0)
		execute_pwd(1);
	if (ft_strncmp(cmd->simple_cmd, "cd", 3) == 0)
		execute_cd(cmd, our_env_var);
	if (ft_strncmp(cmd->simple_cmd, "env", 4) == 0)
		print_env(our_env_var->our_envp);
	if (ft_strncmp(cmd->simple_cmd, "unset", 6) == 0)
        unset_env(cmd->args[0], our_env_var);
	if (ft_strncmp(cmd->simple_cmd, "export", 7) == 0)
		execute_export(cmd, our_env_var);
	// if (ft_strncmp(cmd->simple_cmd, "exit", 5) == 0)
		// execute_exit();
	
}