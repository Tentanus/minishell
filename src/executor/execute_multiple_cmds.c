/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_multiple_cmds.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:47:39 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/11 12:28:00 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	execute_last_cmd(t_minishell *mini, \
	t_cmd *current_cmd,	int prev_read_end)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (mini_error(error_print, 1, \
			"fork: Resource temporarily unavailable"), ERROR);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(prev_read_end, STDIN_FILENO);
		close(prev_read_end);
		if (builtin_check(current_cmd->args[0]) == true)
			handle_builtin(current_cmd, mini);
		else
			handle_non_builtin(current_cmd, mini);
		exit(ft_atoi(g_status));
	}
	close(prev_read_end);
	return (pid);
}

void	execute_child(t_minishell *mini, \
	t_cmd *current_cmd, int *fd_pipe, int prev_read_end)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd_pipe[READ]);
	dup2(prev_read_end, STDIN_FILENO);
	dup2(fd_pipe[WRITE], STDOUT_FILENO);
	close(fd_pipe[WRITE]);
	if (builtin_check(current_cmd->args[0]) == true)
		handle_builtin(current_cmd, mini);
	else
		handle_non_builtin(current_cmd, mini);
	exit(ft_atoi(g_status));
}

int	set_fds(int *fd_pipe, int prev_read_end)
{
	close(fd_pipe[WRITE]);
	if (prev_read_end != 0)
		close(prev_read_end);
	prev_read_end = dup(fd_pipe[READ]);
	close(fd_pipe[READ]);
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
	prev_read_end = STDIN_FILENO;
	current_cmd = mini->cmd_list;
	while (current_cmd->next != NULL)
	{
		count_childs++;
		if (pipe(fd_pipe) < 0)
			return (mini_error(error_print, ERROR, "Pipe fail"));
		pid = fork();
		if (pid < 0)
			return (mini_error(error_print, 1, \
				"fork: Resource temporarily unavailable"));
		if (pid == 0)
			execute_child(mini, current_cmd, fd_pipe, prev_read_end);
		prev_read_end = set_fds(fd_pipe, prev_read_end);
		current_cmd = current_cmd->next;
	}
	pid = execute_last_cmd(mini, current_cmd, prev_read_end);
	wait_function(pid, count_childs);
}
