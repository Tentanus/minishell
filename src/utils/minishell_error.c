#include <libft.h>
#include <stdio.h>
#include <errno.h>

void	minishell_error(const char *loc)
{
	ft_putstr_fd("ERROR IN:\t", 2);
	ft_putendl_fd(loc, 2);
	perror(NULL);
	exit(errno);
}
