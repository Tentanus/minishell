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
** The return status is 0 if the directory is successfully changed, non-zero otherwise.
*/

char	*builtin_cd_get_new_working_dir(t_cmd *cmd, t_env_var_ll **env_var_list)
{
	char	*new_working_dir;

	// new_working_dir = malloc((sizeof(new_working_dir))*1024);
	if (cmd->args[1] == NULL) // this is the case for "cd" without path: that 1 arg = NULL
		new_working_dir = ft_strdup(env_var_get_env("HOME", *env_var_list)); // ! MALLOC
	else if (cmd->args[1][0] == '~')
	{
		if (cmd->args[1][1] == '/')
			new_working_dir = ft_strjoin(env_var_get_env("HOME", *env_var_list), &cmd->args[1][1]); // ! MALLOC
		else
			new_working_dir = ft_strdup(env_var_get_env("HOME", *env_var_list)); // ! MALLOC
	}
	else
	{
		if (ft_strncmp(&cmd->args[1][0], "-", 2) == 0)
		{
			new_working_dir = ft_strdup(env_var_get_env("OLDPWD", *env_var_list)); // ! MALLOC
			if (new_working_dir == NULL) // check if OLDPWD exists, if not:
				return (free(new_working_dir), mini_error_test(error_print, 1, "cd: OLDPWD not set"), NULL);
		}
		else
			new_working_dir = ft_strdup(cmd->args[1]); // ! MALLOC
	}
	return (new_working_dir);
}

int		builtin_cd(t_cmd *cmd, t_env_var_ll **env_var_list)
{
	char	*current_working_dir = NULL;
	char	*pwd;
	char	*cwd;
	char	*new_working_dir;

	new_working_dir = builtin_cd_get_new_working_dir(cmd, env_var_list);
	if (new_working_dir == NULL)
		return (SUCCESS); // exit cd, make sure executor does not execute non-builtin after this
	current_working_dir = ft_strjoin("OLDPWD=", env_var_get_env("PWD", *env_var_list));  // ! MALLOC
	// current_working_dir = NULL;
	if (!current_working_dir)
		return (free(new_working_dir), mini_error_test(error_print, 1, "(malloc) error current_working_dir in execute_cd"), SUCCESS);
	printf("hier?\n");
	if (chdir(new_working_dir) != 0)
		return (mini_error_test(error, 1, cmd->args[1]), SUCCESS);
	env_var_set_env(current_working_dir, env_var_list);
	free(current_working_dir); // ! FREE
	if (cmd->args[1] != NULL && ft_strncmp(&cmd->args[1][0], "-", 2) == 0)
		builtin_pwd(1);
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	pwd = ft_strjoin("PWD=", cwd); // ! MALLOC
	if (!pwd)
		return (free(cwd), minishell_error("error pwd in execute_cd"), ERROR);
	env_var_set_env(pwd, env_var_list);
	free(cwd); // ! FREE
	free(pwd); // ! FREE
	free(new_working_dir); // ! FREE
	return (SUCCESS);
}

/*

1. set new_working_dir:
'cd'				: change cwd to "HOME"
'cd -'				: change cwd to previous working directory (OLDPWD), ignore other arguments AND PRINT new cwd
'cd .'				: change cwd to current working directory aka does nothing
'cd ..'				: change cwd to directory 'above' cwd
'cd ~'				: change cwd to "HOME" of current user
'cd ~/path'			: change cwd to "HOME + path" of current user
'cd ~username'		: DOEN WE NIET
'cd relative path'	: change cwd to relative path
'cd absolute path'	: change cwd to absolute path

2. save current working directory into "OLDPWD=" in envp list

3. change cwd to new working directory with chdir()
chdir() = 0 indicates success: the operating system updates the process's current working directory

4. save new working directory into "PWD=" in envp list

*/
