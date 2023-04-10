#include <minishell.h>

void	wait_function(pid_t pid, int count_childs)
{
    int	status;

	// TODO Wait functie: save pids and wait for pid here / if (WIFEXITED(status)) -> exit(WEXITSTATUS(status));
	// parent must wait for last command/ child process to finish before printing to shell prompt
	if (waitpid(pid, &status, 0) < 0)
		return (minishell_error("waitpid error"));
	while (count_childs > 0)
	{
		wait(NULL);
		count_childs--;
	}
}

/*
	Handles (input and output) redirection.
	Loops through ALL the redirections which are stored
	in a linked list for every command.
*/

void	handle_redirect(t_cmd *cmd)
{
	int		fd_file;

	while (cmd->redir != NULL)
	{
		if (cmd->redir->redir == IN)
		{
			fd_file = open(cmd->redir->file, O_RDONLY);
			if (fd_file < 0)
				return (minishell_error("failed to open input file"));
			if (dup2(fd_file, STDIN_FILENO) == -1)
				return (minishell_error("Dup error stdinput < - > infile\n"));
			close(fd_file);
		}
		else if (cmd->redir->redir == OUT)
		{
			fd_file = open(cmd->redir->file, O_TRUNC | O_CREAT | O_RDWR, 0644);
			if (fd_file < 0 || (access(cmd->redir->file, W_OK) != 0))
				return (minishell_error("failed to open output file"));
			if (dup2(fd_file, STDOUT_FILENO) == -1)
				return (minishell_error("Dup error stdoutput < - > outfile\n"));
			close(fd_file);
		}
		cmd->redir = cmd->redir->next;
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
	if (!mini->cmd_list)
		return ;
	if (mini->cmd_list->next == NULL)
		execute_single_command(mini);
	else
		execute_multiple_commands(mini);
}
