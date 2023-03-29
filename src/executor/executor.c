#include <minishell.h>

// ! NOT MY CODE!
int count_env_vars(t_env_var_ll *head)
{
    int count = 0;
    t_env_var_ll *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

char **env_vars_to_envp(t_env_var_ll *head)
{
    int i = 0;
    t_env_var_ll *current = head;
    char **envp = malloc(sizeof(char *) * (count_env_vars(head) + 1));

    while (current != NULL) {
        if (current->has_value) {
            envp[i] = malloc(strlen(current->name) + strlen(current->value) + 2);
            sprintf(envp[i], "%s=%s", current->name, current->value);
        } else {
            envp[i] = malloc(strlen(current->name) + 1);
            sprintf(envp[i], "%s=", current->name);
        }
        current = current->next;
        i++;
    }
    envp[i] = NULL;
    return envp;
}
// ! NOT MY CODE!

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

char	*get_path_to_cmd(t_minishell *mini)
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
	cmd = ft_strjoin("/", mini->cmd_list->args[0]);
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
/*
	Handles output (redirection)
*/
void handle_output(t_cmd *cmd)
{
    int     fd_file;
	t_redir *redirect;

	redirect = cmd->redir;
    while(redirect != NULL)
    {
		// handle output redirection
		if (redirect->redir == OUT) // check if there is output redirection
		{
			fd_file = open(redirect->file, O_TRUNC | O_CREAT | O_RDWR, 0644); // if so: open outfile and save it in fd_file
			if (fd_file < 0 || (access(redirect->file, W_OK) != 0))
				return (minishell_error("failed to open output file"));
			if (dup2(fd_file, STDOUT_FILENO) == -1) // redirect stdout to fd_file
				return (minishell_error("Dup error stdoutput < - > outfile\n"));
			close(fd_file);	
		}
        redirect = redirect->next;
    }
}

/*
	Handles input (redirection)
*/
void handle_input(t_cmd *cmd)
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
			if (fd_file < 0 || (access(redirect->file, R_OK) != 0))
				return (minishell_error("failed to open input file"));
			if (dup2(fd_file, STDIN_FILENO) == -1) // redirect stdin to fd_file
				return (minishell_error("Dup error stdinput < - > infile\n"));
			close(fd_file);
		}
        redirect = redirect->next;
    }
}

void    handle_non_builtin(t_cmd *cmd, t_minishell *mini)
{
    char    *path_to_cmd;
	char	**env_list;

	// if (cmd->redir != NULL) // check for redirect
    //     handle_redirect(cmd);
    path_to_cmd = get_path_to_cmd(mini);
	env_list = env_vars_to_envp(mini->env_list);
    execve(path_to_cmd, cmd->args, env_list);
    return (minishell_error("execve non_builtin_execute"));
}

void    handle_builtin(t_cmd *cmd, t_minishell *mini)
{
	int tmp_fd;

	tmp_fd = dup(1);
	if (cmd->redir != NULL) // check for redirect
		handle_redirect(cmd);
	builtin_execute(cmd, &mini->env_list); // execute builtin in parent
	dup2(tmp_fd, 1);
	close(tmp_fd);
}

/*
	Sets up pipe for inter-process communication
*/
void set_up_pipe(int *fd_pipe)
{
    if (pipe(fd_pipe) < 0)
        return (minishell_error("Pipe failed"));
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1) // Redirect stdout to write end of pipe
        return (minishell_error("dup2 error for write end of pipe"));
    if (close(fd_pipe[1]) == -1) // Close write end of pipe
		return (minishell_error("close fd_pipe[1] error"));
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1) // Redirect stdin to read end of pipe
        return (minishell_error("dup2 error for read end of pipe"));
    if (close(fd_pipe[0]) == -1) // Close read end of pipe
		return (minishell_error("close fd_pipe[0] error"));
}

int	dup_fds(int fd, int std_fd)
{
	if (fd == std_fd)
		return SUCCESS;
	if (dup2(fd, std_fd) == ERROR)
		return (minishell_error("Dup error\n"), ERROR);
	// close(fd);
	return SUCCESS;
}

int	handle_input_redirect(t_cmd *cmd)
{
	int	fd_file = 0;

	// handle input redirection
	if (cmd->redir == NULL) // if there's no file redirection
		return (dup_fds(fd_file, STDIN_FILENO)); // redirect stdin to fd_file
	while(cmd->redir != NULL)
	{
		if (cmd->redir->redir == IN) // check if there is input file redirection
		{
			fd_file = open(cmd->redir->file, O_RDONLY); // if so: open infile and save it in fd_file
			if (fd_file < 0 || (access(cmd->redir->file, R_OK) != 0))
				return (minishell_error("failed to open input file"), ERROR);
		}
		// handle HEREDOC redirection
		// if (cmd->redir->redir == HERE) // check if there is heredoc redirection
		// {
			// heredoc_function();
		// }
		cmd->redir = cmd->redir->next;
	}
	return (dup_fds(fd_file, STDIN_FILENO)); // redirect stdin to fd_file
}

int	handle_output_redirect(t_cmd *cmd)
{
	int		fd_file = 0;

	// handle output redirection
	if (cmd->next != NULL) // there's a command coming after this current one
		return (dup_fds(fd_pipe[WRITE], STDOUT_FILENO)); // Redirect stdout to write end of pipe
	if (cmd->redir == NULL) // check for redirect
		return (dup_fds(fd_file, STDOUT_FILENO));
    while(cmd->redir != NULL)
    {
		if (cmd->redir->redir == OUT) // check if there is output redirection
		{
			fd_file = open(cmd->redir->file, O_TRUNC | O_CREAT | O_RDWR, 0644); // if so: open outfile and save it in fd_file
			if (fd_file < 0 || (access(cmd->redir->file, W_OK) != 0))
				return (minishell_error("failed to open output file"), ERROR);
		}
		// handle APPEND redirection
		// if (cmd->redir->redir == APP) // check if there is append redirection
		// {
		// 	fd_file = open(cmd->redir->file, O_WRONLY | O_APPEND | O_CREAT, 0644); // if so: open outfile and save it in fd_file
		// 	if (fd_file < 0 || (access(cmd->redir->file, W_OK) != 0))
		// 		return (minishell_error("failed to open append file"), ERROR);
		// }
		cmd->redir = cmd->redir->next;
    }
	return (dup_fds(fd_file, STDOUT_FILENO)); // redirect stdout to fd_file
}

void    execute_multiple_commands(t_minishell *mini)
{
    t_cmd       *current_cmd;
    int         fd_pipe[2];
	pid_t       pid;
    int         status;

	current_cmd = mini->cmd_list;
    while (current_cmd != NULL) // loop through linked list s_cmd made of t_cmd's:
    {
		if (pipe(fd_pipe) < 0) // set up pipe
        	return (minishell_error("Pipe failed"));
		pid = fork(); // fork to create child process
		if (pid < 0)
			return (minishell_error("fork fail"));
		if (pid == 0) // let child process execute cmd
		{
			handle_input_redirect(current_cmd);
			handle_output_redirect(current_cmd);
			if (builtin_check(current_cmd->args[0]) == true) // if command is builtin
			{
				printf("\n\nmultiple commands BUILTIN command = %s\n\n", current_cmd->args[0]);
				builtin_execute(current_cmd, &mini->env_list); // execute builtin
			}
			if (builtin_check(current_cmd->args[0]) == false)  // if command is not builtin
			{
				printf("\n\nmultiple commands non-builtin command = %s\n\n", current_cmd->args[0]);
				handle_non_builtin(current_cmd, mini);
			}
		}
		else // parent process
		{
			// parent must wait for last command/ child process to finish before printing to shell prompt
			if (waitpid(pid, &status, 0) < 0)
				return (minishell_error("waitpid error"));
		}
        current_cmd = current_cmd->next; // move to next node (simple cmd) in linked list
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
    t_cmd       *current_cmd;
	pid_t       pid;
	// int			status;

	current_cmd = mini->cmd_list;
	// if (current_cmd->redir != NULL) // also handle redirect if cmd is empty (&& current_cmd->args == NULL)
	// {
	// 	handle_redirect(current_cmd); // handle redirect
	// 	printf("current_cmd->redir != NULL\n");
	// 	return ;
	// }
	if (builtin_check(current_cmd->args[0]) == true) // let parent process execute builtin cmd
	{
		printf("single command BUILTIN\n");
		// int tmp_fd;
		// tmp_fd = dup(1);
		handle_builtin(current_cmd, mini);
		// dup2(tmp_fd, 1);
		// close(tmp_fd);
		return ;
	}
	else
	{
		printf("single command non-builtin\n");
		pid = fork(); // create child process
		if (pid < 0)
			return (minishell_error("fork fail"));
		if (pid == 0) // let child process execute non-builtin cmd
			handle_non_builtin(current_cmd, mini);
		// else
		// {
			// parent must wait for child process to finish before printing to shell prompt
		// 	if (waitpid(pid, &status, 0) < 0)
		// 		return (minishell_error("waitpid error"));
		// }
	}
}

/*
	executor() is the executing part of our minishell.
    It is fully based on the command table
    as is outputed by the lexer, parser and expander.
	For every command, redirection is handled.
    Builtin commands are executed in parent process.
    Non-builtin commands are executed in child process after forking.
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
