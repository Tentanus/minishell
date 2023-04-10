#include <minishell.h>

pid_t	execute_last_cmd(t_minishell *mini, t_cmd *current_cmd, int prev_read_end)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (minishell_error("fork fail"), -1);
	if (pid == 0)
	{
		dup2(prev_read_end, STDIN_FILENO); // duplicate the read end of the previous pipe to standard input
		close(prev_read_end);
		if (current_cmd->args[0] != NULL) // if cmd is not empty
		{
			// fprintf(stderr, "\n\nexecuting LAST command = %s\n", current_cmd->args[0]);
			if (handle_builtin(current_cmd, mini) != SUCCESS) // if command is builtin, it's executed
				handle_non_builtin(current_cmd, mini); // handle redirect and execute non builtin
		}
		else // if cmd is empty
		{
			// fprintf(stderr, "\n\nexecuting LAST command = EMPTY\n");
			if (current_cmd->redir != NULL) // always handle redirections, even if cmd is empty
				handle_redirect(current_cmd);
		}
		exit(EXIT_SUCCESS); // TODO change exit code
	}
	// printf("pid: %d\tcmd: %s\n", pid, current_cmd->args[0]);
	close(prev_read_end);
	return (pid);
}

void	execute_child(t_minishell *mini, t_cmd *current_cmd, int *fd_pipe, int prev_read_end)
{
	close(fd_pipe[READ]); // close the read end of the pipe
	dup2(prev_read_end, STDIN_FILENO); // duplicate the read end of the previous pipe to standard input
	dup2(fd_pipe[WRITE], STDOUT_FILENO); // duplicate the write end of the current pipe to standard output
	close(fd_pipe[WRITE]); // close the write end of the pipe
	if (current_cmd->args[0] != NULL) // if cmd is not empty
	{
		// fprintf(stderr, "\n\nnon-last command = %s\n", current_cmd->args[0]);
		if (handle_builtin(current_cmd, mini) != SUCCESS) // if command is builtin, it's executed
			handle_non_builtin(current_cmd, mini); // handle redirect and execute non builtin
	}
	else // if cmd is empty
	{
		// fprintf(stderr, "\n\nnon-last command = EMPTY\n");
		if (current_cmd->redir != NULL) // always handle redirections, even if cmd is empty
			handle_redirect(current_cmd);
	}
	exit(EXIT_SUCCESS); // TODO change exit code
}

int	set_fds(int *fd_pipe, int prev_read_end)
{
	close(fd_pipe[WRITE]); // close the write end of the current pipe
	// ? close prev_read_end only if heredoc
	if (prev_read_end != 0)
		close(prev_read_end); // close the read end of the previous pipe
	prev_read_end = dup(fd_pipe[READ]); // save the read end of the current pipe for the next iteration
	close(fd_pipe[READ]); // close the read end of the pipe
	return (prev_read_end);
}

void	execute_multiple_commands(t_minishell *mini)
{
	t_cmd	*current_cmd;
	pid_t	pid;
	int		fd_pipe[2];
	int		prev_read_end;
	int		count_childs;

	count_childs = 0;
	prev_read_end = STDIN_FILENO; // initialize the read end of the first pipe to standard input
	current_cmd = mini->cmd_list;
	while (current_cmd->next != NULL) // loop through linked list s_cmd made of t_cmd's, if current_cmd is not last cmd:
	{
		count_childs++;
		// ? handle heredoc
		if (pipe(fd_pipe) < 0)
			return (minishell_error("Pipe fail"));
		pid = fork();
		if (pid < 0)
			return (minishell_error("Fork fail"));
		if (pid == 0)
			execute_child(mini, current_cmd, fd_pipe, prev_read_end);
		prev_read_end = set_fds(fd_pipe, prev_read_end);
		// printf("pid: %d\tcmd: %s\n", pid, current_cmd->args[0]);
		current_cmd = current_cmd->next; // move to next node (simple cmd) in linked list
	}
	pid = execute_last_cmd(mini, current_cmd, prev_read_end); // last command in the pipeline
	wait_function(pid, count_childs);
}
