#include <minishell.h>

// char	*free_and_return(char *cmd, char **sub_paths, char *tmp)
// {
// 	free(cmd);
// 	free_double_array(sub_paths);
// 	return (tmp);
// }

// /*
// 	get_path_to_cmd() makes all possible subpaths+cmds
// 	and checks if accessibility of the (path to) cmd.
// 	If accessible path is found, this path is returned.
// 	If not, null string is returned.
// */

// char	*get_path_to_cmd(t_minishell *mini)
// {
// 	char	*path_complete;
//     char	**sub_paths;
//     char    *cmd;
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	tmp = NULL;
// 	path_complete = env_var_get_env("PATH", mini->env_list); // TODO handle PATH does not exist!
// 	if (path_complete == NULL)
//         minishell_error("PATH does not exist");
//     sub_paths = ft_split(path_complete, ':');
// 	if (!sub_paths)
// 		exit(127);
// 	cmd = ft_strjoin("/", mini->cmd_list->args[0]);
// 	if (!cmd)
// 		exit(127);
// 	while (sub_paths[i] != NULL)
// 	{
// 		tmp = ft_strjoin(sub_paths[i], cmd);
// 		if (!tmp)
// 			exit(127);
// 		if (access(tmp, X_OK) == 0)
// 			return (free_and_return(cmd, sub_paths, tmp));
// 		free(tmp);
// 		i++;
// 	}
// 	return (free_and_return(cmd, sub_paths, tmp));
// }

// void    non_builtin_execute(t_cmd *cmd, t_minishell *mini)
// {
//     char    *path_to_cmd;

//     // we are in child process
//     path_to_cmd = get_path_to_cmd(mini);
//     // execve(path_to_cmd, cmd->args, mini->env_list);
//     // execve(path_to_cmd, cmd->args, envp);
//     return (minishell_error("execve non_builtin_execute"));
// }

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
			// close(fd_file);
		}
		// handle output redirection
		else if (redirect->redir == OUT) // check if there is output redirection
		{
			// printf("BLA2\n");
			fd_file = open(redirect->file, O_TRUNC | O_CREAT | O_RDWR, 0644); // if so: open outfile and save it in fd_file
			// printf("BLA3\n");
			if (fd_file < 0 || (access(redirect->file, W_OK) != 0))
				return (minishell_error("failed to open output file"));
			// printf("BLA4\n");
			// printf("fd_file = %i\n", fd_file);
			if (dup2(fd_file, STDOUT_FILENO) == -1) // redirect stdout to fd_file
				return (minishell_error("Dup error stdoutput < - > outfile\n"));
			close(fd_file);
			// printf("BLA5\n");
			// if (fd_file == 0 || fd_file == 1)
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
	Sets up pipe for inter-process communication
*/
void set_up_pipe(int *fd_pipe)
{
    if (pipe(fd_pipe) < 0)
        return (minishell_error("Pipe failed"));
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1) // Redirect stdout to write end of pipe
        return (minishell_error("dup2 error for write end of pipe"));
    close(fd_pipe[1]); // Close write end of pipe
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1) // Redirect stdin to read end of pipe
        return (minishell_error("dup2 error for read end of pipe"));
    close(fd_pipe[0]); // Close read end of pipe
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
	t_cmd	    *current_cmd;
    int			fd_pipe[2];
	pid_t		pid;
    int         status;
	int			tmp_fd; // only needed for builtins/cmds executed by parent?

	current_cmd = mini->cmd_list;
	while (current_cmd != NULL) // loop through linked list s_cmd made of t_cmd's:
    {
        if (current_cmd->args[0] != NULL) // check if cmd is not empty
        {
			tmp_fd = dup(1); // ! TAKE A LOOK AT THIS!
            if (current_cmd->next != NULL) // more than 1 cmd!
                set_up_pipe(fd_pipe);
            if (current_cmd->redir != NULL) // check for redirect // ? WAAR MOET DIT?
                handle_redirect(current_cmd);
            if (builtin_check(mini->cmd_list->args[0]) == true)// check for builtin
                builtin_execute(mini->cmd_list, &mini->env_list); // execute builtin in parent
			else if (builtin_check(mini->cmd_list->args[0]) == false) // if cmd is non-builtin
            {
                pid = fork(); // create child process
                if (pid < 0)
                    return (minishell_error("fork fail"));
                // if (pid == 0) // let child process execute cmd
                //     non_builtin_execute(current_cmd, mini);
                else
                {
                    // parent must wait for last command/ child process to finish before printing to shell prompt
                    if (waitpid(pid, &status, 0) < 0)
                        return (minishell_error("waitpid error"));
                }
            }
			// ! TAKE A LOOK AT THIS:
			dup2(tmp_fd, 1);
			close(tmp_fd);
        }
        current_cmd = current_cmd->next; // move to next node in linked list
    }
	// TODO if (WIFEXITED(status)) -> exit(WEXITSTATUS(status));
}

// if (pid == 0) // let child process execute cmd
//     non_builtin_execute(current_cmd, mini);
// else
// {
//     // parent must wait for last command/ child process to finish before printing to shell prompt
//     if (waitpid(pid, &status, 0) < 0)
//         return (minishell_error("waitpid error"));
// }
    
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