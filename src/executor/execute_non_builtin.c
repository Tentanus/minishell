#include <minishell.h>

char	*free_and_return(char *cmd, char **sub_paths, char *path_cmd)
{
	free(cmd);
	free_double_array(sub_paths);
	return (path_cmd);
}

char	*find_path(char	**sub_paths, char *cmd)
{
	char	*path_cmd;
	int		i;

	i = 0;
	path_cmd = NULL;
	while (sub_paths[i] != NULL)
	{
		path_cmd = ft_strjoin(sub_paths[i], cmd); // ! MALLOC
		if (!path_cmd)
		{
			free_and_return(cmd, sub_paths, path_cmd);
			minishell_error("Error in strjoin sub_path[i] + /cmd");
		}
		if (access(path_cmd, X_OK) == 0)
			return (free_and_return(cmd, sub_paths, path_cmd));
		free(path_cmd);
		i++;
	}
	return (free_and_return(cmd, sub_paths, path_cmd));
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
	char	*cmd;
	char	**sub_paths;

	path_complete = env_var_get_env("PATH", mini->env_list);
	if (path_complete == NULL) // if PATH does not exist
		minishell_error("PATH does not exist");
	if (!current_cmd->args[0]) // if cmd does not exist
		minishell_error("cmd does not exist");
	if (ft_strncmp(current_cmd->args[0], "./", 2) == 0 || ft_strncmp(current_cmd->args[0], "/", 1) == 0 ) // if cmd starts with ./
	{
		if (access(current_cmd->args[0], X_OK) == 0)
			return (current_cmd->args[0]);
		else
			return (minishell_error(current_cmd->args[0]), NULL);
	}
	cmd = ft_strjoin("/", current_cmd->args[0]); // ! MALLOC
	if (!cmd)
		minishell_error("Error in strjoin \"/\" + cmd");
	sub_paths = ft_split(path_complete, ':'); // ! MALLOC
	if (!sub_paths)
	{
		free(cmd);
		minishell_error("Error in split subpaths");
	}
	return (find_path(sub_paths, cmd));
}

void	handle_non_builtin(t_cmd *cmd, t_minishell *mini)
{
	char	*path_to_cmd;
	char	**env_list;

	if (cmd->redir != NULL) // check for redirect
		handle_redirect(cmd);
	path_to_cmd = get_path_to_cmd(mini, cmd);
	if (path_to_cmd != NULL)
	{
		env_list = env_var_to_cpp(mini->env_list);
		// printf("cmd->args[0] = %s\n", cmd->args[0])
		// printf("path_to_cmd = %s\n", path_to_cmd);
		// fprintf(stderr, "executing NON builtin command = %s\n\n", cmd->args[0]);
		if (execve(path_to_cmd, cmd->args, env_list) != SUCCESS)
			return (minishell_error_exit(cmd->args[0]));
		// return (minishell_error("execve non_builtin_execute"));
	}
}
