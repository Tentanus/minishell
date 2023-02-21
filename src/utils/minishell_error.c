#include <libft.h>
#include <stdio.h>
#include <errno.h>
#include <minishell.h>

void	minishell_error(const char *loc)
{
	ft_putstr_fd("ERROR IN:\t", 2);
	ft_putendl_fd(loc, 2);
	perror(NULL);
	exit(errno);
}

void	minishell_syntax_error(t_token token)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(token.str, 2);
	ft_putendl_fd("'", 2);
	exit(errno);
}
