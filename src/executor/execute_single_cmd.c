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

	pid = fork();
	if (pid < 0)
		return (minishell_error("fork fail"));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); // !
		signal(SIGQUIT, SIG_DFL); // !
		handle_non_builtin(current_cmd, mini);
	}
	else
		wait_function(pid, 0);
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

	tmp_fd_in = dup(0);
	tmp_fd_out = dup(1);
	current_cmd = mini->cmd_list;
	if (current_cmd->args[0] == NULL) // even if cmd is empty:
		handle_redirect(current_cmd->redir, mini_error_test); // fprintf(stderr, "no command yes redirection\n");
	else if (handle_builtin(current_cmd, mini) != SUCCESS)
		execute_single_child(current_cmd, mini);
	return (set_back_std_fd(tmp_fd_in, tmp_fd_out));
}
