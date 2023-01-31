/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_paths.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/23 11:55:02 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/10/06 16:36:10 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*
	find_path_complete() searches full path in envp.
	Returns full path if found.
	If not, it returns null string.
*/

char	*find_path_complete(char **envp)
{
	char	*path_complete;
	char	*path;
	int		i;

	path = "PATH=";
	path_complete = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(path, envp[i], 5) == 0)
			break ;
		i++;
	}
	path_complete = ft_strtrim(envp[i], path);
	if (!path_complete)
		exit(127);
	return (path_complete);
}

char	*free_and_return(char *cmd, char **sub_paths, char *tmp)
{
	free(cmd);
	free_array(sub_paths);
	return (tmp);
}

/*
	get_path_to_cmd() makes all possible subpaths+cmds
	and checks if accessibility of the (path to) cmd.
	If accessible path is found, this path is returned.
	If not, null string is returned.
*/

char	*get_path_to_cmd(char *cmd, char *path_complete)
{
	char	**sub_paths;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	sub_paths = ft_split(path_complete, ':');
	if (!sub_paths)
		exit(127);
	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		exit(127);
	while (sub_paths[i] != NULL)
	{
		tmp = ft_strjoin(sub_paths[i], cmd);
		if (!tmp)
			exit(127);
		if (access(tmp, X_OK) == 0)
			return (free_and_return(cmd, sub_paths, tmp));
		free(tmp);
		i++;
	}
	return (free_and_return(cmd, sub_paths, tmp));
}

/*
	check_cmd returns path to cmd if cmd-input is absolute or executable,
	if not, it calls get_path_to_cmd to find right path to cmd.
*/

char	*check_cmd(char **input_split, char *path_complete)
{
	char	*path_to_cmd;

	path_to_cmd = NULL;
	if (access(*input_split, X_OK) == 0
		|| input_split[0][0] == '/' || input_split[0][0] == '.')
		return (input_split[0]);
	path_to_cmd = get_path_to_cmd(input_split[0], path_complete);
	if (!path_to_cmd)
		exit(127);
	return (path_to_cmd);
}

/*
	checks() tests:
	if cmd1 exists of space (returns 1)
	if cmd1 is empty (returns 2)
	if cmd2 exists of space (returns 3)
	if cmd2 is empty (returns 4)
*/

int	checks(char **argv)
{
	if (str_is_space(argv[2]) == 0)
		return (1);
	if (str_is_space(argv[2]) == 2)
		return (2);
	if (str_is_space(argv[3]) == 0)
		return (3);
	if (str_is_space(argv[3]) == 2)
		return (4);
	return (0);
}
