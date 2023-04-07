#include <minishell.h>

/*
	Handles (input and output) redirection.
	Loops through ALL the redirections which are stored
	in a linked list for every command.
*/

void	handle_redirect(t_cmd *cmd)
{
	int		fd_file;
	t_redir	*redirect;

	redirect = cmd->redir;
	while (redirect != NULL)
	{
		// handle input redirection
		if (redirect->redir == IN) // check if there is input redirection
		{
			fd_file = open(redirect->file, O_RDONLY); // if so: open infile and save it in fd_file
			if (fd_file < 0)
				return (minishell_error("failed to open input file"));
			if (dup2(fd_file, STDIN_FILENO) == -1) // redirect stdin to fd_file
				return (minishell_error("Dup error stdinput < - > infile\n"));
			close(fd_file);
		}
		// handle output redirection
		else if (redirect->redir == OUT) // check if there is output redirection
		{
			fd_file = open(redirect->file, O_TRUNC | O_CREAT | O_RDWR, 0644); // if so: open outfile and save it in fd_file
			if (fd_file < 0 || (access(redirect->file, W_OK) != 0))
				return (minishell_error("failed to open output file"));
			if (dup2(fd_file, STDOUT_FILENO) == -1) // redirect stdout to fd_file
				return (minishell_error("Dup error stdoutput < - > outfile\n"));
			close(fd_file);
		}
        // handle append redirection
        // else if (redirect->redir == APP) // check if there is append redirection
        // {
        //     fd_file = open(redirect->file, O_WRONLY | O_APPEND | O_CREAT, 0644); // if so: open outfile and save it in fd_file
        //     if (fd_file < 0)
        //         return (minishell_error("failed to open append file"));
        //     if (dup2(fd_file, STDOUT_FILENO) == -1) // redirect stdout to fd_file
        //         return (minishell_error("Dup error stdoutput < - > write end of pipe\n"));
        //     close(fd_file);
        // }
		redirect = redirect->next;
	}
}

/*
	executor() is the executing part of our minishell.
    It is fully based on the command table
    as is outputed by the complexer (lexer, parser and expander).
	It first checks if complex command exists of one simple command or multiple simple commands.
*/

void	executor(t_minishell *mini)
{
	if (!mini->cmd_list)
		return ;
	if (mini->cmd_list->next == NULL) // only one cmd!
		execute_single_command(mini);
	else
		execute_multiple_commands(mini);
}

/*
NOTES:
dup2(old_fd, new_fd):
The dup2() function duplicates the old file descriptor to the new (standard) file descriptor,
which means that any subsequent write to the new_fd (standard output) will actually write to old_fd (the file).
if (dup2(old_fd, new_fd) == -1) // redirect from old_fd to new_fd
	return (ERROR and close(new_fd))

The close() function must close the file descriptor that was returned by open().
*/
