/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_non_builtin.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:39:56 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/12 16:07:47 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*free_and_return(char *cmd, char **sub_paths, char *path_cmd)
{
	free(cmd);
	ft_free_split(sub_paths);
	return (path_cmd);
}

char	*find_path(char	**sub_paths, char *cmd)
{
	char	*path_cmd;
	char	*tmp_cmd;
	int		i;

	i = 0;
	path_cmd = NULL;
	tmp_cmd = ft_strjoin("/", cmd);
	if (!tmp_cmd)
		return (ft_free_split(sub_paths), mini_error(error_print, \
			ERROR, "(malloc) error in strjoin tmp_cmd + /cmd"), NULL);
	while (sub_paths[i] != NULL)
	{
		path_cmd = ft_strjoin(sub_paths[i], tmp_cmd);
		if (!path_cmd)
		{
			mini_error(error_print, ERROR, \
				"Error in strjoin sub_path[i] + /cmd");
			free_and_return(tmp_cmd, sub_paths, path_cmd);
		}
		if (access(path_cmd, X_OK) == 0)
			return (free_and_return(tmp_cmd, sub_paths, path_cmd));
		free(path_cmd);
		i++;
	}
	return (free_and_return(tmp_cmd, sub_paths, cmd));
}

/*
	get_path_to_cmd() makes all possible subpaths+cmds
	and checks if accessibility of the (path to) cmd.
	If accessible path is found, this path is returned.
	If not, null string is returned.
*/

char	*get_path_to_cmd(t_minishell *mini, t_cmd *current_cmd)
{
	char	*path_complete;
	char	**sub_paths;

	path_complete = env_var_get_env("PATH", mini->env_list);
	if (!current_cmd->args[0])
		mini_error(error_print, ERROR, "cmd does not exist");
	if (ft_strncmp(current_cmd->args[0], "./", 2) == 0 || \
		ft_strncmp(current_cmd->args[0], "/", 1) == 0)
	{
		if (access(current_cmd->args[0], X_OK) == 0)
			return (current_cmd->args[0]);
		else
			mini_exit_child(error, 127, current_cmd->args[0]);
	}
	sub_paths = ft_split(path_complete, ':');
	if (!sub_paths)
		mini_error(error_print, ERROR, "Error in split subpaths");
	return (find_path(sub_paths, current_cmd->args[0]));
}

void	handle_non_builtin(t_cmd *cmd, t_minishell *mini)
{
	char	*path_to_cmd;
	char	**env_list;

	if (handle_redirect(cmd->redir, mini_exit_child) == ERROR)
		_exit(1);
	if (cmd->args[0] == NULL)
		return (status_update(0));
	path_to_cmd = get_path_to_cmd(mini, cmd);
	env_list = list_env_var_convert_to_cpp(mini->env_list);
	if (execve(path_to_cmd, cmd->args, env_list) != SUCCESS)
	{
		ft_free_split(env_list);
		if (cmd->args[0][0] == '\0' || access(path_to_cmd, F_OK) == ERROR)
			mini_exit_child(cmd_error, 127, cmd->args[0]);
		if (access(path_to_cmd, X_OK) == ERROR)
			mini_exit_child(error, 126, cmd->args[0]);
		errno = 21;
		mini_exit_child(error, 126, cmd->args[0]);
	}
}
