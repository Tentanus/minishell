/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:05:05 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/02/09 18:09:32 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// bool    check_builtin(char *cmd)
// {
// 	if (ft_strncmp(cmd, "echo", 5) == 0)
//         return(true);
//     if (ft_strncmp(cmd, "cd", 3) == 0)
//         return(true);
//     if (ft_strncmp(cmd, "pwd", 4) == 0)
//         return(true);
//     if (ft_strncmp(cmd, "export", 7) == 0)
//         return(true);
//     if (ft_strncmp(cmd, "unset", 6) == 0)
//         return(true);
//     if (ft_strncmp(cmd, "env", 4) == 0)
//         return(true);
//     if (ft_strncmp(cmd, "exit", 5) == 0)
//         return(true);
//     return (false);
// }

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
	if (ft_strncmp(cmd->simple_cmd, "unset", 7) == 0)
        unset_env(cmd->args[0], our_env_var);
}

// void    execute_builtin(t_args *arg, t_cmd *cmd)
// {
//     if (ft_strncmp(arg->cmd2_split[0], "echo", 5) == 0)
//         execute_echo(arg, cmd);
//     if (ft_strncmp(cmd, "cd", 3) == 0)
//         return(true);
//     if (ft_strncmp(cmd, "pwd", 4) == 0)
//         return(true);
//     if (ft_strncmp(cmd, "export", 8) == 0)
//         return(true);
//     if (ft_strncmp(cmd, "unset", 7) == 0)
//         return(true);
//     if (ft_strncmp(cmd, "env", 4) == 0)
//         return(true);
//     if (ft_strncmp(cmd, "exit", 5) == 0)
//         return(true);
// }
