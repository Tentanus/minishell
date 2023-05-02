#include <libft.h>
#include <stdio.h>
#include <errno.h>
#include <minishell.h>

int	minishell_chdir_error(const char *cmd, const char *arg)
{
	ft_putstr_fd("marsh: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	return (SUCCESS);
}

void	minishell_cd_error(const char *loc)
{
	ft_putstr_fd("marsh: ", 2);
	ft_putstr_fd(loc, 2);
	return ;
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

//------------------------------------------------------------

void	syntax_error(const char *token)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}

void	error_print(const char *str)
{
	ft_putendl_fd(str, 2);
}

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


/*
als fd op -1 komt te staan return error in child process

 */
