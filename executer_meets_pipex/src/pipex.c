/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 18:14:40 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/01/19 14:42:12 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	close_pipe_ends(int *fd_pipe)
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	return ;
}

/*
	read_child executes first command.
    It reads from infile instead of standard input (first dup2 call).
    It writes output to write end of pipe = fd_pipe[1]
    (with second dup2 call) instead of standard output.
    This output will be input for the second command.
*/

void	read_child(int *fd_pipe, t_args *arg, char **argv, char **envp)
{
	int		fd_file;
	char	*info;

	fd_file = open(arg->infile, O_RDONLY);
	if (fd_file < 0)
	{
		info = arg->infile;
		arg->infile = "NULL";
		double_error_message(errno, info);
	}
	if (dup2(fd_file, STDIN_FILENO) == -1)
		exit_message("Dup error stdinput < - > infile\n", 3);
	close(fd_file);
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		exit_message("Dup error stdoutput < - > write end of pipe\n", 4);
	close_pipe_ends(fd_pipe);
	if (execve(arg->path_to_cmd1, arg->cmd1_split, envp) != 0)
		handle_execve1_fail(arg, argv);
}

/*
	write_parent executes second command.
    It reads from read end of pipe = fd_pipe[0]
    instead of standard input (first dup2 call)
	where it receives cmd1.
    It writes output to outfile (with second dup2 call)
    instead of standard output.
*/

void	write_parent(int *fd_pipe, t_args *arg, char **argv, char **envp, int argc)
{
	int	fd_file;

	fd_file = open(arg->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_file < 0 || (access(arg->outfile, W_OK) != 0))
		double_error_message_code(errno, 1, arg->outfile);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		exit_message("Dup error stdinput < - > read end of pipe\n", 5);
	close_pipe_ends(fd_pipe);
	if (dup2(fd_file, STDOUT_FILENO) == -1)
		exit_message("Dup error stdoutput < - > outfile\n", 6);
	close(fd_file);
	// !!!! TESTING BUILTINS!
	if (check_builtin(arg->cmd2_split[0]) == true)
		execute_builtin(arg->cmd2_split[0], argc, argv);
	// !!!! END
	else if (execve(arg->path_to_cmd2, arg->cmd2_split, envp) != 0)
	{
		if (checks(argv) == 3)
			cmd_not_found("command not found:", 127, "");
		if (checks(argv) == 4)
			cmd_not_found("permission denied:", 126, "");
		if (access(*arg->cmd2_split, X_OK) != 0 && arg->cmd2_split[0][0] != '/')
			cmd_not_found("command not found: ", 127, arg->cmd2_split[0]);
		double_error_message(errno, arg->cmd2_split[0]);
	}
	exit(127);
}

/*
	Pipex function creates one pipe and one child process:
	pid is the current process id. 
    If pid == 0, we're in the child process.
    If pid > 0, we're in the parent process.
    the read_child for the first command, executed in the child process.
    and the write_child for the second command, executed by the main process.
    parent waits for child to finish execution.
*/

int	pipex(int argc, char **argv, t_args *arg, char **envp)
{
	int	fd_pipe[2];
	int	pid;
	int	status;

	if (argc == 5)
	{
		parse_input(arg, argv, envp);
		if (pipe(fd_pipe) == -1)
			exit_message("Pipe failed\n", 1);
		pid = fork();
		if (pid == -1)
			exit_message("Fork failed\n", 2);
		if (pid == 0)
			read_child(fd_pipe, arg, argv, envp);
		write_parent(fd_pipe, arg, argv, envp, argc);
		close_pipe_ends(fd_pipe);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit(WEXITSTATUS(status));
		return (0);
	}
	return (arg_error());
}

int	main(int argc, char **argv, char **envp)
{
	t_args	arg;
	// t_cmd	cmd;

	return (pipex(argc, argv, &arg, envp));
}
