/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 11:14:57 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/01/16 10:46:07 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h" // for libft
# include <string.h> // for strerror
# include <fcntl.h> // for open
# include <stdlib.h> // for free, exit
# include <unistd.h> // for close, write, access, dup2, execve, fork, pipe
# include <errno.h> // for errors
# include <sys/wait.h> // for waitpid

#include <stdio.h> // for printf
#include <stdbool.h> // for bool

typedef struct struct_args
{
	char	*infile;
	char	*outfile;
	char	**cmd1_split;
	char	**cmd2_split;
	char	*path_to_cmd1;
	char	*path_to_cmd2;
}	t_args;

int		pipex(int argc, char **argv, t_args *arg, char **envp);
void	write_parent(int *fd_pipe, t_args *arg, char **argv, char **envp);
void	read_child(int *fd_pipe, t_args *arg, char **argv, char **envp);
void	close_pipe_ends(int *fd_pipe);

void	parse_input(t_args *arg, char **argv, char **envp);
char	**get_cmd(char *input);
void	cmd2(t_args *arg, char **argv, char *path_complete);
void	cmd1(t_args *arg, char **argv, char *path_complete);

int		checks(char **argv);
char	*check_cmd(char **input_split, char *path_complete);
char	*get_path_to_cmd(char *cmd, char *path_complete);
char	*free_and_return(char *cmd, char **sub_paths, char *tmp);
char	*find_path_complete(char **envp);

int		arg_error(void);
void	cmd_not_found(char *error_message, int code, char *info);
void	exit_message(char *error_message, int code);
void	double_error_message(int exit_code, char *info);
void	double_error_message_code(int code, int exit_code, char *info);

char	**free_array(char **array);
char	**check_sed(char **input_split, int word_count);
int		str_is_space(char *str);
void	handle_execve1_fail(t_args *arg, char **argv);

int		ft_word_counter(char const *s, char c);

bool    check_builtin(char *cmd);
void    execute_builtin(char *str);
void    our_echo(char *str);


#endif
