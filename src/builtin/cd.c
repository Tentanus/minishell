#include <minishell.h>

/*
** cd 
** Changes the current working directory.
** If the new_directory is not supplied, the value of the HOME shell variable is used.
** If the shell variable CDPATH exists, it is used as a search path:
** each directory name in CDPATH is searched for directory,
** with alternative directory names in CDPATH separated by a colon (‘:’).
** If directory begins with a slash, CDPATH is not used.
*/

int	execute_cd(t_cmd *cmd, char **envp) 
{
	char *new_working_dir;
	char *current_working_dir = NULL;
	char *old_pwd;
	char *pwd = NULL;
	int	chdir_return;
	bool to_print = false;

	// 1. set new_working_dir
	if (cmd->amount_of_args == 1) // this is the case for "cd" without path: that 1 arg = NULL
		new_working_dir = getenv("HOME");
	else
	{
		// handle "cd -": change cwd to previous working directory OLDPWD
		if (ft_strncmp(&cmd->args[0][0], "-", 2) == 0)
		{
			old_pwd = getenv("OLDPWD"); // get OLDPWD
			printf("we zijn in cd - en old_pwd = %s\n", old_pwd);
			if (old_pwd == NULL) // check if OLDPWD exists, if not:
			{
				minishell_error("cd: OLDPWD not set"); // throw error like bash
				return (1);
			}
			new_working_dir = old_pwd;
			// (ignore other args)
			// print cwd! met execute_pwd() ?
			to_print = true;
		}
		else
			new_working_dir = cmd->args[0];
	}
	// printf("new_working_dir = %s\n", new_working_dir);

	// 2. save current working directory into "OLDPWD=" environment variable
	current_working_dir = getcwd(current_working_dir, 0);
	set_env("OLDPWD", current_working_dir, envp);
	// printf("current_working_dir = %s\n", current_working_dir);

	//  3. change working directory PWD to new_directory
	//  chdir() = 0 (indicating success): the operating system updates the process's
	//  current working directory
	chdir_return = chdir(new_working_dir);
	if (chdir_return != 0)
	{
		minishell_error("chdir error. cd: args[0]"); // throw error like bash
		return (1);
	}
	if (to_print == true)
		execute_pwd(1); // change 1 to fd?

	// 4. save new_working_dir in PWD in envp list
	pwd = getcwd(pwd, 0);
	// printf("pwd = %s\n", pwd);
	set_env("PWD", pwd, envp);

	// system("leaks martest");
	// printf("envp at the end of execute_cd:\n\n");
	// print_env(envp);
	return (0);
}

// 1. SET new_working_dir:
// - cd zonder arg: change cwd to "HOME"
// - cd met 1 arg: change cwd to arg[0]
// - "cd -": should take the user back to previous working directory (OLDPWD)
// cd met arg[0][0] == '-': change cwd to previous working directory OLDPWD (ignore other args), print cwd!
// let op! old pwd does not necessarily exist
// if arg[0][0] == '-'

// 2. save current_working_dir in OLDPWD in envp list

// 3. CHANGE cwd met chdir()
// change working directory PWD to new_directory
// CHECK IF new_working_directory (arg[0]) EXISTS!!!

// 4. save new_working_dir in PWD in envp list

// (expanding tilde in the path)
