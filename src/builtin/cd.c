/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:30:17 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/16 16:08:15 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** cd
** Changes the current working directory.
** If the new_directory is not supplied, the value of the HOME shell variable
** is used.
** If the directory change is successful, cd sets the value of the
** PWD environment variable to the new directory name,
** and sets the OLDPWD environment variable to the value of the
** current working directory BEFORE the change.
** The return status is 0 if the directory is successfully changed,
** non-zero otherwise.
*/

char	*builtin_cd_get_new_working_dir(t_cmd *cmd, t_env_var_ll **env_var_list)
{
	char	*nwd;

	if (cmd->args[1] == NULL)
		nwd = ft_strdup(env_var_get_env("HOME", *env_var_list));
	else if (ft_strncmp(&cmd->args[1][0], "~", 2) == 0)
		nwd = ft_strdup(env_var_get_env("HOME", *env_var_list));
	else if (ft_strncmp(&cmd->args[1][0], "~/", 2) == 0)
		nwd = ft_strjoin(env_var_get_env("HOME", \
			*env_var_list), &cmd->args[1][1]);
	else if (cmd->args[1][0] == '-')
	{
		if (ft_strncmp(&cmd->args[1][0], "-", 2) == 0)
			nwd = ft_strdup(env_var_get_env("OLDPWD", *env_var_list));
		else if (ft_strncmp(&cmd->args[1][0], "--", 3) == 0)
			nwd = ft_strdup(env_var_get_env("HOME", *env_var_list));
		else
			return (mini_error(error_print, 1, "cd: invalid option"), NULL);
		if (nwd == NULL)
			return (free(nwd), mini_error(error_print, 1, \
				"cd: OLDPWD not set"), NULL);
	}
	else
		nwd = ft_strdup(cmd->args[1]);
	return (nwd);
}

int	change_directory(t_cmd *cmd, t_env_var_ll **env_var_list)
{
	char	*new_working_dir;
	char	*current_working_dir;
	char	*cwd;

	new_working_dir = builtin_cd_get_new_working_dir(cmd, env_var_list);
	if (new_working_dir == NULL)
		return (ERROR);
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	current_working_dir = ft_strjoin("OLDPWD=", cwd);
	if (!current_working_dir)
		return (free(cwd), free(new_working_dir), mini_error(error_print, 1, \
			"(malloc) error current_working_dir in execute_cd"), MALLOC_ERROR);
	free(cwd);
	if (chdir(new_working_dir) != 0)
		return (free(current_working_dir), free(new_working_dir), \
			mini_error(error, 1, cmd->args[1]), ERROR);
	env_var_set_env(current_working_dir, env_var_list);
	free(current_working_dir);
	free(new_working_dir);
	return (SUCCESS);
}

int	builtin_cd(t_cmd *cmd, t_env_var_ll **env_var_list)
{
	char	*pwd;
	char	*cwd;

	if (change_directory(cmd, env_var_list) == SUCCESS)
	{
		if (cmd->args[1] != NULL && ft_strncmp(&cmd->args[1][0], "-", 2) == 0)
			builtin_pwd(1);
		cwd = NULL;
		cwd = getcwd(cwd, 0);
		pwd = ft_strjoin("PWD=", cwd);
		if (!pwd)
			return (free(cwd), mini_error(error_print, 1, \
				"(malloc) error pwd in execute_cd"), MALLOC_ERROR);
		env_var_set_env(pwd, env_var_list);
		free(cwd);
		free(pwd);
		return (SUCCESS);
	}
	return (ERROR);
}

/*
1. set new_working_dir:
'cd'				: change cwd to "HOME"
'cd -'				: change cwd to previous working directory (OLDPWD),
ignore other arguments AND PRINT new cwd
'cd .'				: change cwd to current working directory aka does nothing
'cd ..'				: change cwd to directory 'above' cwd
'cd ~'				: change cwd to "HOME" of current user
'cd ~/path'			: change cwd to "HOME + path" of current user
'cd relative path'	: change cwd to relative path
'cd absolute path'	: change cwd to absolute path
2. save current working directory into "OLDPWD=" in envp list
3. change cwd to new working directory with chdir()
chdir() = 0 indicates success: the operating system updates
the process's current working directory
4. save new working directory into "PWD=" in envp list
*/
