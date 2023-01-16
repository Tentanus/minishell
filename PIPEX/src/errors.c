/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:33:42 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/10/06 16:32:55 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	double_error_message_code(int code, int exit_code, char *info)
{
	write(2, "mares-pipex: ", 14);
	write(2, strerror(code), ft_strlen(strerror(code)));
	write(2, ": ", 2);
	write(2, info, ft_strlen(info));
	write(2, "\n", 1);
	exit(exit_code);
}

void	double_error_message(int exit_code, char *info)
{
	write(2, "mares-pipex: ", 14);
	write(2, strerror(exit_code), ft_strlen(strerror(exit_code)));
	write(2, ": ", 2);
	write(2, info, ft_strlen(info));
	write(2, "\n", 1);
	exit(127);
}

void	exit_message(char *error_message, int code)
{
	write(2, "mares-pipex: ", 14);
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	exit(code);
}

void	cmd_not_found(char *error_message, int code, char *info)
{
	write(2, "mares-pipex: ", 14);
	write(2, error_message, ft_strlen(error_message));
	write(2, info, ft_strlen(info));
	write(2, "\n", 1);
	exit(code);
}

int	arg_error(void)
{
	char	*error;

	error = "Incorrect amount of arguments given!\nExecute this way:\n"
		" $> ./pipex file1 cmd1 cmd2 file2\n";
	write(2, "mares-pipex: ", 14);
	write(2, error, ft_strlen(error));
	return (1);
}
