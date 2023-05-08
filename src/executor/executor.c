/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:40:02 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/08 13:51:04 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_function(pid_t pid, int count_childs)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
		return (mini_error_test(error_print, ERROR, "Waitpid error"));
	while (count_childs > 0)
	{
		wait(NULL);
		count_childs--;
	}
	if (WIFEXITED(status))
		status_update(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("^\\Quit: 3", 1);
		else if (WTERMSIG(status) == SIGINT)
			ft_putendl_fd("^C", 1);
		status_update(status + 128);
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
	signal(SIGINT, SIG_IGN);
	if (!mini->cmd_list)
		return ;
	if (handle_here_doc(mini->cmd_list, mini->env_list) == -1)
		close_here_doc(mini->cmd_list);
	if (mini->cmd_list->next == NULL)
		execute_single_command(mini);
	else
		execute_multiple_commands(mini);
	close_here_doc(mini->cmd_list);
	list_cmd_free_list(mini->cmd_list);
	mini->cmd_list = NULL;
}
