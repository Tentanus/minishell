/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_error.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:41:29 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/11 11:31:20 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	mini_error(void (*func)(const char *), \
		int status, const char *str)
{
	ft_putstr_fd("marsh: ", 2);
	func(str);
	status_update((unsigned int) status);
}

void	mini_exit(void (*func)(const char *), \
		int status, const char *str)
{
	ft_putstr_fd("marsh: ", 2);
	func(str);
	exit(status);
}

void	mini_exit_child(void (*func)(const char *), \
		int status, const char *str)
{
	ft_putstr_fd("marsh: ", 2);
	func(str);
	_exit(status);
}
