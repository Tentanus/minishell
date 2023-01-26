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

int	execute_cd(t_cmd *cmd, t_env *env, char **envp)
{
	char *new_working_dir;
	char *old_working_dir = NULL;
	char *cwd = NULL;
	int	chdir_return;
	bool to_print = false;

	// set new_working_dir
	if (cmd->amount_of_args == 0)
		new_working_dir = getenv("HOME");
	else
	{
		// handle "cd -": change cwd to previous working directory OLDPWD
		if (ft_strncmp(&cmd->args[0][0], "-", 2) == 0)
		{
			char *OLDWD = getenv("OLDPWD"); // get OLDPWD
			printf("OLDWD = %s\n", OLDWD);
			printf("PWD = %s\n", getenv("PWD"));
			if (!OLDWD) // check if OLDPWD exists, if not:
			{
				perror("cd: OLDPWD not set"); // throw error like bash
				return (1);
			}
			new_working_dir = OLDWD;
			env->OLDPWD = new_working_dir;
			// (ignore other args)
			// print cwd! met execute_pwd() ?
			to_print = true;
		}
		else
			new_working_dir = cmd->args[0];
	}
	printf("new_working_dir = %s\n", new_working_dir);

	// save current working directory into old_working_dir ("OLDPWD= " ???)
	cwd = getcwd(cwd, 0);
	printf("cwd = %s\n", cwd);
	ft_strlcpy(old_working_dir, cwd, ft_strlen(cwd));
	// printf("ft_strlen(cwd) = %zu\n", ft_strlen(cwd));
	// printf("old_working_dir = %s\n", old_working_dir); // WERKT NIET??

	//  change working directory PWD to new_directory
	chdir_return = chdir(new_working_dir);
	if (chdir_return != 0)
	{
		perror("cd: args[0]");
		return (1);
	}
	else // remove later when finished
	{
		char *new_cwd = NULL;
		new_cwd = getcwd(new_cwd, 0);
		printf("new_cwd: %s\n", new_cwd);
	}

	printf("dit is een test %s\n", getenv(envp[6]));

	if (to_print == true)
		execute_pwd(1); // change 1 to fd?
	// printf("cmd->amount_of_args = %d\n", cmd->amount_of_args);
	return (0);
}

// - SET new_working_dir:
// cd zonder arg: change cwd to "HOME"
// cd met 1 arg: CHECK IF arg[0] EXISTS and change cwd to arg[0]

// - handling the - argument (should take the user back to previous working directory (OLDPWD))
// cd met arg[0][0] == '-': change cwd to previous working directory OLDPWD (ignore other args), print cwd!
// if arg[0][0] == '-'
// save oldpwd in tmp
// change oldpwd to cwd
// change cwd to tmp

// - SAVE the value of the OLDPWD environment variables
// old pwd does not necessarily exist
// if cd: save cwd in OLDPWD by using getenv("PWD")

// CHANGE cwd met chdir()
// change working directory PWD to new_directory

// - expanding tilde in the path
