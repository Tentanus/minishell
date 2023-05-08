/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_error_custom.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:41:48 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/08 13:41:49 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	syntax_error(const char *token)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}

void	export_error(const char *name)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
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
