#include <libft.h>
#include <stdio.h>
#include <errno.h>
#include <minishell.h>

void	minishell_error(const char *loc)
{
	ft_putstr_fd("marsh: ERROR IN:\t", 2);
	ft_putendl_fd(loc, 2);
	perror(NULL);
	exit(errno);
}

void	minishell_syntax_error(const char *token)
{
	ft_putstr_fd("marsh: syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}

void	minishell_quote_error(void)
{
	ft_putendl_fd("marsh: unclosed quotes", 2);
}
