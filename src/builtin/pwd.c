#include <minishell.h>

/*
** pwd
** Prints the absolute pathname of the current working directory.
** The return status is zero unless an error is encountered
** while determining the name of the current directory
** or an invalid option is supplied.
*/

int    execute_pwd(int fd)
{
    char    *cwd = NULL;
    cwd = getcwd(cwd, sizeof(cwd));
    ft_putstr_fd(cwd, fd);
    ft_putstr_fd("\n", fd);
    return (0);
}
