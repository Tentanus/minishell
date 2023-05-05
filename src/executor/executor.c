#include <minishell.h>

void	wait_function(pid_t pid, int count_childs)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0) // let parent wait for last executed command/process, specified with pid
		return (mini_error_test(error_print, ERROR, "Waitpid error"));
	while (count_childs > 0) // wait for all child processes
	{
		wait(NULL);
		count_childs--;
	}
	if (WIFEXITED(status)) // if last cmd exited normally (by calling exit or returning to main)
		status_update(WEXITSTATUS(status)); // exit with exit status of last command
	if (WIFSIGNALED(status)) // if last cmd terminated by call of a signal
	{
		if (WTERMSIG(status) == SIGQUIT) // ctrl-backslash
			ft_putendl_fd("^\\Quit: 3", 1); // naar fd 1 of 2?
		else if (WTERMSIG(status) == SIGINT) // ctrl-c
			ft_putendl_fd("^C", 1); // naar fd 1 of 2?
		status_update(status + 128); // lekker hardcoding whiii
	}
}

/*
	executor() is the executing part of our minishell.
    It is fully based on the command table
    as is outputed by the complexer (lexer, parser and expander).
	It first checks if complex command exists of
	one simple command or multiple simple commands.
*/

void	executor(t_minishell *mini)
{
	signal(SIGINT, SIG_IGN); // !
	if (!mini->cmd_list)
		return ;
	if (handle_here_doc(mini->cmd_list, mini->env_list) == -1)
	{
		close_here_doc(mini->cmd_list);
		list_cmd_free_list(mini->cmd_list);
		mini->cmd_list = NULL;
		return ;
	}
	if (mini->cmd_list->next == NULL)
		execute_single_command(mini);
	else
		execute_multiple_commands(mini);
	close_here_doc(mini->cmd_list);
	list_cmd_free_list(mini->cmd_list);
	mini->cmd_list = NULL;
}
