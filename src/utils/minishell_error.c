#include <libft.h>
#include <stdio.h>
#include <errno.h>
#include <minishell.h>


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

//------------------------------------------------------------

void	minishell_quote_error(void)
{
	ft_putendl_fd("marsh: unclosed quotes", 2);
}

void	syntax_error(const char *token)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}
//------------------------------------------------------------

void	export_error(const char *name)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
	// perror(NULL);
}

void	cmd_error(const char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
}

void	chdir_error(const char *cmd)
{
	ft_putendl_fd("cd: ", 2);
	ft_putstr_fd(cmd, 2);
	perror(NULL);
}

void	error(const char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
}

void	error_print(const char *str)
{
	ft_putendl_fd(str, 2);
}

//------------------------------------------------------------

void	mini_error_test(void (*func)(const char *), \
		int status, const char *str)
{
	ft_putstr_fd("marsh: ", 2);
	func(str);
	status_update((unsigned int) status);
}

void	mini_exit_test(void (*func)(const char *), \
		int status, const char *str)
{
	ft_putstr_fd("marsh: ", 2);
	func(str);
	exit(status);
}
