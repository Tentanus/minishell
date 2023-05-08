#include <minishell.h>

/*
** pwd
** Prints the absolute pathname of the current working directory.
** The return status is zero unless an error is encountered
** while determining the name of the current directory
** or an invalid option is supplied.
*/

int	builtin_pwd(int fd)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
		return (mini_error(error_print, 1, "pwd error"), MALLOC_ERROR);
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
	free(cwd);
	return (SUCCESS);
}
