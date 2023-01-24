#include <minishell.h>

/*
** cd 
** Changes the current working directory to directory.
** If directory is not supplied, the value of the HOME shell variable is used.
** If the shell variable CDPATH exists, it is used as a search path:
** each directory name in CDPATH is searched for directory,
** with alternative directory names in CDPATH separated by a colon (‘:’).
** If directory begins with a slash, CDPATH is not used.
*/

int	execute_cd(t_cmd *cmd)
{
	int	chdir_return;
	char *path;

	printf("cmd->amount_of_args = %d\n", cmd->amount_of_args);
	if (cmd->amount_of_args == 0)
		path = getenv("HOME");
	else
		path = cmd->args[0];
	printf("path = %s\n", path);
	chdir_return = chdir(path);
	if (chdir_return != 0)
	{
		perror("cd error");
		return (1);
	}
	else
	{
		printf("changing directory to: %s\n", path);
	}
	return (0);
}
