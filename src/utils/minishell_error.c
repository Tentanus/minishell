#include <libft.h>
#include <stdio.h>
#include <errno.h>
#include <minishell.h>

int	minishell_cd_error(const char *cmd, const char *arg)
{
	ft_putstr_fd("marsh: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	return (SUCCESS);
}

void	minishell_error(const char *loc)
{
	ft_putstr_fd("marsh: ", 2);
	ft_putstr_fd(loc, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	return ;
}

void	minishell_error_exit(const char *loc)
{
	ft_putstr_fd("marsh: ", 2);
	ft_putstr_fd(loc, 2);
	ft_putstr_fd(": ", 2);
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
