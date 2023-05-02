#include <minishell.h>

void	wait_function(pid_t pid, int count_childs)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0) // let parent wait for last executed command/process, specified with pid
		return (minishell_error("waitpid error"));
	while (count_childs > 0) // wait for all child processes
	{
		wait(NULL);
		count_childs--;
	}
	// if (WIFEXITED(status)) // if last cmd exited normally
	status_update(WEXITSTATUS(status)); // exit with exit status of last command
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
	handle_here_doc(mini->cmd_list, mini->env_list);
	if (mini->cmd_list->next == NULL)
		execute_single_command(mini);
	else
		execute_multiple_commands(mini);
	close_here_doc(mini->cmd_list);
}
