/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_old.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:05:05 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/03/01 11:47:23 by mverbrug      ########   odam.nl         */
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

// ! include minishell.h
// bool	get_env_var_exists(char *name); // old old, making use of getenv()
// bool	env_var_exists(char *name, char **envp);
// char	*get_env(char *name, t_env_var *envars); 
// void	set_env(char *name, char *value, t_env_var *envars);
// int		search_for_env_index(char *name, char **envp);
// int		get_end_of_envp_list(char **envp);
// char	*make_env_var_format(char *name, char *value);
// void	set_our_envp(char **envp, t_env_var *envars);