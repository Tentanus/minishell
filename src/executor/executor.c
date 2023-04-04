#include <minishell.h>

char	*free_and_return(char *cmd, char **sub_paths, char *tmp)
{
	free(cmd);
	free_double_array(sub_paths);
	return (tmp);
}

/*
	get_path_to_cmd() makes all possible subpaths+cmds
	and checks if accessibility of the (path to) cmd.
	If accessible path is found, this path is returned.
	If not, null string is returned.
*/

char	*get_path_to_cmd(t_minishell *mini, t_cmd *current_cmd)
{
	char	*path_complete;
    char	**sub_paths;
    char    *cmd;
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	path_complete = env_var_get_env("PATH", mini->env_list); // TODO handle PATH does not exist!
	if (path_complete == NULL)
        minishell_error("PATH does not exist");
    sub_paths = ft_split(path_complete, ':');
	if (!sub_paths)
		exit(127);
	cmd = ft_strjoin("/", current_cmd->args[0]);
	if (!cmd)
		exit(127);
	while (sub_paths[i] != NULL)
	{
		tmp = ft_strjoin(sub_paths[i], cmd);
		if (!tmp)
			exit(127);
		if (access(tmp, X_OK) == 0)
			return (free_and_return(cmd, sub_paths, tmp));
		free(tmp);
		i++;
	}
	return (free_and_return(cmd, sub_paths, tmp));
}


/*
	Handles (input and output) redirection
*/
void handle_redirect(t_cmd *cmd)
{
    int     fd_file;
	t_redir *redirect;

	redirect = cmd->redir;
    while(redirect != NULL)
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

void    handle_non_builtin(t_cmd *cmd, t_minishell *mini)
{
    char    *path_to_cmd;
	char	**env_list;

	if (cmd->redir != NULL) // check for redirect
        handle_redirect(cmd);
    path_to_cmd = get_path_to_cmd(mini, cmd);
	env_list = env_var_to_cpp(mini->env_list);
	// printf("cmd->args[0] = %s\n", cmd->args[0]);
	// printf("path_to_cmd = %s\n", path_to_cmd);
	fprintf(stderr, "executing NON builtin command = %s\n\n", cmd->args[0]);
    execve(path_to_cmd, cmd->args, env_list);
    return (minishell_error("execve non_builtin_execute"));
}

int	handle_builtin(t_cmd *cmd, t_minishell *mini)
{
	// int tmp_fd;

	// tmp_fd = dup(1);
	if (cmd->redir != NULL) // check for redirect
		handle_redirect(cmd);
	if (builtin_check(cmd->args[0]) == true)
	{
		fprintf(stderr, "executing builtin command = %s\n\n", cmd->args[0]);
		return (builtin_execute(cmd, &mini->env_list)); // execute builtin in parent
	}
	else
		return (ERROR);
	// dup2(tmp_fd, 1);
	// close(tmp_fd);
}
void    set_back_std_fd(int tmp_fd_in, int tmp_fd_out)
{
    dup2(tmp_fd_in, 0);
	dup2(tmp_fd_out, 1);
	close(tmp_fd_in);
	close(tmp_fd_out);
}

void	execute_last_cmd(t_minishell *mini, t_cmd *current_cmd, int prev_read_end)
{
	pid_t       pid;
    int         status;

	pid = fork(); // fork to create child process
	if (pid < 0)
		return (minishell_error("fork fail"));
	if (pid == 0) // let child process execute cmd
	{
		dup2(prev_read_end, STDIN_FILENO); // duplicate the read end of the previous pipe to standard input
		close(prev_read_end);
		if (current_cmd->args[0] != NULL) // if cmd is not empty
		{
			fprintf(stderr, "\n\nexecuting LAST command = %s\n", current_cmd->args[0]);
			if (handle_builtin(current_cmd, mini) != SUCCESS) // if command is builtin, it's executed
				handle_non_builtin(current_cmd, mini); // handle redirect and execute non builtin
		}
		else // if cmd is empty
		{
			fprintf(stderr, "\n\nexecuting LAST command = EMPTY\n");
			if (current_cmd->redir != NULL) // always handle redirections, even if cmd is empty 
				handle_redirect(current_cmd);
		}
		exit(EXIT_SUCCESS); // TODO change exit code
	}
	close(prev_read_end);
	// close(STDOUT_FILENO);
	// parent must wait for last command/ child process to finish before printing to shell prompt
	if (waitpid(pid, &status, 0) < 0)
		return (minishell_error("waitpid error"));
}

void    execute_multiple_commands(t_minishell *mini)
{
    t_cmd       *current_cmd;
    int         fd_pipe[2];
	pid_t       pid;
    int         status;
	int			prev_read_end;

	int		tmp_fd_in = 0;
	int		tmp_fd_out = 0;

	tmp_fd_in = dup(0);
	tmp_fd_out = dup(1);

	prev_read_end = STDIN_FILENO; // initialize the read end of the first pipe to standard input
	current_cmd = mini->cmd_list;
    while (current_cmd->next != NULL) // loop through linked list s_cmd made of t_cmd's, if current_cmd is not last cmd:
    {
		if (pipe(fd_pipe) < 0) // set up pipe
			return (minishell_error("Pipe failed"));
		pid = fork(); // fork to create child process
		if (pid < 0)
			return (minishell_error("fork fail"));
		if (pid == 0) // let child process execute cmd
		{
			close(fd_pipe[READ]); // close the read end of the pipe
			dup2(prev_read_end, STDIN_FILENO); // duplicate the read end of the previous pipe to standard input
			dup2(fd_pipe[WRITE], STDOUT_FILENO); // duplicate the write end of the current pipe to standard output
			close(fd_pipe[WRITE]); // close the write end of the pipe
			if (current_cmd->args[0] != NULL) // if cmd is not empty
			{
				fprintf(stderr, "\n\nnon-last command = %s\n", current_cmd->args[0]);
				if (handle_builtin(current_cmd, mini) != SUCCESS) // if command is builtin, it's executed
					handle_non_builtin(current_cmd, mini); // handle redirect and execute non builtin
			}
			else // if cmd is empty
			{
				fprintf(stderr, "\n\nnon-last command = EMPTY\n");
				if (current_cmd->redir != NULL) // always handle redirections, even if cmd is empty 
					handle_redirect(current_cmd);
			}
			exit(EXIT_SUCCESS); // TODO change exit code
		}
		close(fd_pipe[WRITE]); // close the write end of the current pipe
		close(prev_read_end); // close the read end of the previous pipe
		prev_read_end = dup(fd_pipe[READ]); // save the read end of the current pipe for the next iteration
		close(fd_pipe[READ]); // close the read end of the pipe
		// parent must wait for last command/ child process to finish before printing to shell prompt
		if (waitpid(pid, &status, 0) < 0)
			return (minishell_error("waitpid error"));
		current_cmd = current_cmd->next; // move to next node (simple cmd) in linked list
	}
	// last command in the pipeline
	execute_last_cmd(mini, current_cmd, prev_read_end);
	set_back_std_fd(tmp_fd_in, tmp_fd_out);
}


void	execute_child(t_cmd *current_cmd, t_minishell *mini)
{
	pid_t       pid;
	int			status;

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
	For every command, redirection is handled.
    Builtin commands are executed in parent process.
    Non-builtin commands are executed in child process after forking.
*/
void    execute_single_command(t_minishell *mini)
{
    t_cmd	*current_cmd;
	int		tmp_fd_in = 0;
	int		tmp_fd_out = 0;

	current_cmd = mini->cmd_list;
	tmp_fd_in = dup(0);
	tmp_fd_out = dup(1);
	if (current_cmd->redir != NULL) // always handle redirections, even if cmd is empty 
		handle_redirect(current_cmd);
	if (current_cmd->args[0] == NULL) // if cmd is empty, set back std fds and return
	{
		fprintf(stderr, "no command yes redirection\n");
		return (set_back_std_fd(tmp_fd_in, tmp_fd_out));
	}
	if (builtin_check(current_cmd->args[0]) == true) // if cmd is builtin, let parent process execute cmd immediately
	{
		fprintf(stderr, "single command BUILTIN\n");
		builtin_execute(current_cmd, &mini->env_list);
	}
	set_back_std_fd(tmp_fd_in, tmp_fd_out);
	if (builtin_check(current_cmd->args[0]) == false) // if cmd non-builtin, fork and let child process execute cmd
	{
		fprintf(stderr, "single command non-builtin\n");
		execute_child(current_cmd, mini);
	}
}

/*
	executor() is the executing part of our minishell.
    It is fully based on the command table
    as is outputed by the complexer (lexer, parser and expander).
*/

void	executor(t_minishell *mini)
{
    if (!mini->cmd_list)
		return ;
	if (mini->cmd_list->next == NULL) // only one cmd!
	{
		printf("single command\n");
        execute_single_command(mini);
	}
    else
	{
		printf("multiple commands\n");
        execute_multiple_commands(mini);
	}
	// TODO 1. save pids and wait for pid here / if (WIFEXITED(status)) -> exit(WEXITSTATUS(status));
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

// !
// ! In this example, we first iterate over each command in the linked list, and for each command,
// ! we set up the appropriate input/output file descriptors based on any redirection specified
// ! in the command.
// ! If the command is a built-in command, we execute it in the parent process using the 
// ! execute_builtin() function.
// ! If the command is not a built-in command, we create a pipe for inter-process communication,
// ! and then fork a child process to execute the command using the execute_command() function,
// ! with the input file descriptor set to cmd_infd and the output file descriptor set to the
// ! write end of the pipe (pipes[1]). After the command has finished executing, we close the
// ! write end of the pipe and set cmd_infd to the read end of the pipe (pipes[0]) so that the
// ! output of the current command becomes the input of the next command.
// !