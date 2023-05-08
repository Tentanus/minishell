/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_single_cmd.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 14:52:21 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/08 15:20:42 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
		return (mini_error(error_print, 1, \
			"fork: Resource temporarily unavailable"));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
	if (current_cmd->args[0] == NULL)
		handle_redirect(current_cmd->redir, mini_error);
	else if (handle_builtin(current_cmd, mini) == ERROR)
		execute_single_child(current_cmd, mini);
	return (set_back_std_fd(tmp_fd_in, tmp_fd_out));
}
