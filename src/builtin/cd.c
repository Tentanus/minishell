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

// int	execute_cd(t_cmd *cmd, t_env_var *our_env_var)
// {
// 	char	*current_working_dir = NULL;
// 	char	*pwd = NULL;
// 	bool	to_print = false;
// 	char	*new_working_dir = NULL;
// 	int		chdir_return;

// 	if (cmd->amount_of_args == 1) // this is the case for "cd" without path: that 1 arg = NULL
// 		new_working_dir = get_env("HOME", our_env_var);
// 	else if (cmd->args[0][0] == '~')
// 	{
// 		if (cmd->args[0][1] == '/')
// 			new_working_dir = ft_strjoin(get_env("HOME", our_env_var), &cmd->args[0][1]);
// 		else
// 			new_working_dir = &cmd->args[0][1];
// 	}
// 	else
// 	{
// 		if (ft_strncmp(&cmd->args[0][0], "-", 2) == 0)
// 		{
// 			new_working_dir = get_env("OLDPWD", our_env_var);
// 			if (new_working_dir == NULL) // check if OLDPWD exists, if not:
// 			{
// 				minishell_error("cd: OLDPWD not set"); // throw error like bash
// 				return (1);
// 			}
// 			to_print = true;
// 		}
// 		else
// 			new_working_dir = cmd->args[0];
// 	}
// 	current_working_dir = get_env("PWD", our_env_var);
// 	set_env("OLDPWD", current_working_dir, our_env_var);

// 	chdir_return = chdir(new_working_dir);
// 	if (chdir_return != 0)
// 	{
// 		minishell_error("chdir error. cd: args[0]"); // throw error like bash
// 		return (1);
// 	}
// 	if (to_print == true)
// 		execute_pwd(1); // change 1 to fd?
// 	pwd = getcwd(pwd, 0);
// 	set_env("PWD", pwd, our_env_var);
// 	free(pwd);
// 	return (0);
// }

/*

1. set new_working_dir:
'cd'				: change cwd to "HOME"
'cd -'				: change cwd to previous working directory (OLDPWD), ignore other arguments AND PRINT new cwd
'cd .'				: change cwd to current working directory aka does nothing
'cd ..'				: change cwd to directory above cwd
'cd ~'				: change cwd to "HOME" of current user
'cd ~/path'			: change cwd to "HOME + path" of current user
'cd ~username'		: DOEN WE NIET
'cd relative path'	: change cwd to relative path
'cd absolute path'	: change cwd to absolute path

2. save current working directory into "OLDPWD=" in envp list

3. change cwd to new working directory with chdir()
? Do I need to check if new_working_directory exists or is chdir doing that?
chdir() = 0 indicates success: the operating system updates the process's current working directory

4. save new working directory into "PWD=" in envp list

*/
