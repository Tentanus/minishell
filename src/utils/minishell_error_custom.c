/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_error_custom.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:41:48 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/12 15:09:33 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	syntax_error(const char *token)
{
	ft_putstr_fd("syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

void	unset_error(const char *name)
{
	ft_putstr_fd("unset: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
}

void	export_error(const char *name)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
}

void	cmd_error(const char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	chdir_error(const char *cmd)
{
	ft_putendl_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	perror(NULL);
}
