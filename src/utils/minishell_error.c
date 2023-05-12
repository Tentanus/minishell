/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_error.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:41:29 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/12 15:09:09 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error(const char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(NULL);
}

void	error_print(const char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
}

void	mini_error(void (*func)(const char *), \
		int status, const char *str)
{
	ft_putstr_fd("marsh: ", STDERR_FILENO);
	func(str);
	status_update((unsigned int) status);
}

void	mini_exit(void (*func)(const char *), \
		int status, const char *str)
{
	ft_putstr_fd("marsh: ", STDERR_FILENO);
	func(str);
	exit(status);
}

void	mini_exit_child(void (*func)(const char *), \
		int status, const char *str)
{
	ft_putstr_fd("marsh: ", STDERR_FILENO);
	func(str);
	_exit(status);
}
