#include <minishell.h>

void	set_back_std_fd(int tmp_fd_in, int tmp_fd_out)
{
	dup2(tmp_fd_in, 0);
	dup2(tmp_fd_out, 1);
	close(tmp_fd_in);
	close(tmp_fd_out);
}

void	execute_single_child(t_cmd *current_cmd, t_minishell *mini)
{
	pid_t	pid;
	int		status;

	pid = fork(); // create child process
	if (pid < 0)
		return (minishell_error("fork fail"));
	if (pid == 0) // let child process execute non-builtin cmd
		handle_non_builtin(current_cmd, mini);
	else // parent must wait for child process to finish before printing to shell prompt
	{
		if (waitpid(pid, &status, 0) < 0)
			return (minishell_error("waitpid error"));
	}
}

/*
	execute_single_command() executes the command.
	STDIN and STDOUT are saved, so redirection can be handled.
	Redirection is always handled, even if command is empty.
    Builtin commands are executed in parent process.
    Non-builtin commands are executed in child process after forking.
	STDIN and STDOUT are put back at the end of execution.
*/

void	execute_single_command(t_minishell *mini)
{
	t_cmd	*current_cmd;
	int		tmp_fd_in;
	int		tmp_fd_out;

	current_cmd = mini->cmd_list;
	tmp_fd_in = dup(0);
	tmp_fd_out = dup(1);
	if (current_cmd->args[0] == NULL) // if cmd is empty, set back std fds and return
	{
		// fprintf(stderr, "\n\ncommand = EMPTY\n");
		if (current_cmd->redir != NULL) // always handle redirections, even if cmd is empty
		{
			// fprintf(stderr, "no command yes redirection\n");
			handle_redirect(current_cmd);
		}
		return (set_back_std_fd(tmp_fd_in, tmp_fd_out));
	}
	// fprintf(stderr, "\n\ncommand = %s\n", current_cmd->args[0]);
	if (handle_builtin(current_cmd, mini) != SUCCESS) // if command is builtin, it's executed
		execute_single_child(current_cmd, mini); // handle redirect and execute non builtin
	return (set_back_std_fd(tmp_fd_in, tmp_fd_out));
}
