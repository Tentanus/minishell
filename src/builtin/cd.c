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
	char *current_working_dir;
	char *old_pwd;
	char *pwd;
	int	chdir_return;
	bool to_print = false;

	// 1. set new_working_dir
	if (cmd->amount_of_args == 0)
		new_working_dir = getenv("HOME");
	else
	{
		// handle "cd -": change cwd to previous working directory OLDPWD
		if (ft_strncmp(&cmd->args[0][0], "-", 2) == 0)
		{
			old_pwd = getenv("OLDPWD"); // get OLDPWD
			// printf("old_pwd = %s\n", old_pwd);
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
	// function to search environment variable (strcmp), look for OLDPWD
	// if function does not exist yet: add/set environment variable
	// if function does exist already: function to modify environment variable
	current_working_dir = getcwd(current_working_dir, 0);
	printf("current_working_dir = %s\n", current_working_dir);
	set_env("OLDPWD", current_working_dir, envp);
	// set_env("USER", "weetikhet", envp);
	set_env("HERTJES", "weetikhet", envp);
	printf("getenv = %s\n", getenv("HERTJES"));
	int result = search_for_env_index("HERTJES", envp);
    if (result != -1)
		printf("env_var found = %s\n\n", envp[result]);
	else
		printf("env_var did not exist (yet)\n\n");

	//  3. change working directory PWD to new_directory
	//  chdir() = 0 (indicating success): the operating system updates the process's
	//  current working directory
	chdir_return = chdir(new_working_dir);
	if (chdir_return != 0)
	{
		minishell_error("chdir error. cd: args[0]"); // throw error like bash 
		return (1);
	}
	else // remove else block later when finished
	{
		char *new_cwd = NULL;
		new_cwd = getcwd(new_cwd, 0);
		printf("new_cwd: %s\n", new_cwd);
	}
	if (to_print == true)
		execute_pwd(1); // change 1 to fd?

	// 4. save new_working_dir in PWD in envp list
	// function to search environment variable (strcmp), look for PWD
	// modify PWD environment variable
	pwd = getcwd(pwd, 0);
	printf("pwd = %s\n", pwd);
	set_env("PWD", pwd, envp);

	// int i = 0;
    // while (envp[i])
    // {
    //     if (strncmp(envp[i], "OLDPWD=", 7) == 0)
    //         envp[i] = current_working_dir;
    //     if (strncmp(envp[i], "PWD=", 4) == 0)
    //         envp[i] = pwd;
    //     i++;
    // }

	print_env(envp); // to test!
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
