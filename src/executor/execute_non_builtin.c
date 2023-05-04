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
	tmp_cmd = ft_strjoin("/", cmd); // ! MALLOC
	if (!tmp_cmd)
		return (ft_free_split(sub_paths), mini_error_test(error_print, ERROR, "(malloc) error in strjoin tmp_cmd + /cmd"), NULL);
	while (sub_paths[i] != NULL)
	{
		path_cmd = ft_strjoin(sub_paths[i], tmp_cmd); // ! MALLOC
		if (!path_cmd)
		{
			mini_error_test(error_print, ERROR, "Error in strjoin sub_path[i] + /cmd");
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
	if (!current_cmd->args[0]) // if cmd does not exist
		mini_error_test(error_print, ERROR, "cmd does not exist");
	if (ft_strncmp(current_cmd->args[0], "./", 2) == 0 || ft_strncmp(current_cmd->args[0], "/", 1) == 0 ) // if cmd starts with ./
	{
		if (access(current_cmd->args[0], X_OK) == 0)
			return (current_cmd->args[0]);
		else
			mini_exit_test(error, 126, current_cmd->args[0]);
	}
	sub_paths = ft_split(path_complete, ':'); // ! MALLOC
	if (!sub_paths)
		mini_error_test(error_print, ERROR, "Error in split subpaths");
	return (find_path(sub_paths, current_cmd->args[0]));
}

void	handle_non_builtin(t_cmd *cmd, t_minishell *mini)
{
	char	*path_to_cmd;
	char	**env_list;

	handle_redirect(cmd->redir, redir_error_exit);
	path_to_cmd = get_path_to_cmd(mini, cmd);
	env_list = env_var_to_cpp(mini->env_list);
	if (execve(path_to_cmd, cmd->args, env_list) != SUCCESS)
	{
		ft_free_split(env_list);
		if (access(path_to_cmd, F_OK) == ERROR)
			mini_exit_test(cmd_error, 127, cmd->args[0]);
		if (access(path_to_cmd, X_OK) == ERROR)
			mini_exit_test(error, 126, cmd->args[0]);
		errno = 21;
		mini_exit_test(error, 126, cmd->args[0]);
	}
}
