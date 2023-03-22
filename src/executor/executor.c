#include <minishell.h>

void    non_builtin_execute()
{
    // we are in child process
	// find paths?
    execve(path_to_cmd, cmd, envp);
    perror(“execve”);
    exit(1);
}


void OLD_handle_redirect()
{
    // store current stdin and stdout into two new fds using dup():
    int fd_in_tmp = dup(0);
    int fd_out_tmp = dup(1);
    
    // set initial input:
    int fd_in;
    // check if there is input redirection
    if (infile)
        fd_in = open(infile, O_RDONLY); // if so: open infile and save it in fd_in
    else
        fd_in = dup(fd_in_tmp); // if not: create fd_in that points to default input
    // fd_in will now be file descriptor that has the input of the command line
    // it can be closed without affecting the parent shell program

    int fd_out;

	dup2(fd_in, 0); // redirect standard input to come from fd_in:
	// any read from stdin will come from file pointed to by fd_in.
	close(fd_in);

	// check if there is a output file redirection like command > outfile
	if (outfile)
		fd_out = open(outfile); // if so: open outfile and save it in fd_out
	else
		fd_out = dup(fd_out_tmp); // if not: create fd_out that points to default output
        
	// NOTE: for these simple commands, output is pipe, not a file!
	// create new pipe
	int fd_pipe[2];
	pipe(fd_pipe);
	fd_out = fd_pipe[1]; // to write
	fd_in = fd_pipe[0]; // to read !!! this makes input fd_in of the next simple command

    // redirect output:
    dup2(fd_out, 1); // redirect stdout to go to the file object pointed to by fd_out
    // now both stdin and stdout have been redirected to either a file or a pipe
    close(fd_out); // fd_out is closed as it is no longer needed

    // restore defaults for input and output for parent
    dup2(fd_in_tmp, 0);
    dup2(fd_out_tmp, 1);
    // close temorary fds
    close(fd_in_tmp);
    close(fd_out_tmp);
    // * still need to set up stderror redirection (fd 2). 
    // * make sure that stderr of ALL simple commands will be send to the same place!
}

void handle_redirect()
{
    int     fd_in;
    int     fd_out;
    int     fd_err;

    // handle input redirection
    if (redirect->redir == IN) // check if there is input redirection
    {
        fd_in = open(cmd->redir->file, O_RDONLY); // if so: open infile and save it in fd_in
        if (fd_in < 0)
            return (perror("failed to open input file"));
    }
    else
    {
        dup2(fd_in, STDIN_FILENO); // redirect stdin to fd_in
	    close(fd_in);
    }

    // handle output redirection
    if (redirect->redir == OUT) // check if there is output redirection
    {
        fd_out = open(cmd->redir->file, O_WRONLY | O_TRUNC | O_CREAT, 0644); // if so: open outfile and save it in fd_out
        if (fd_out < 0)
            return (perror("failed to open output file"));
    }
    else
    {
        dup2(fd_out, STDOUT_FILENO); // redirect stdout to fd_out
	    close(fd_out);
    }

    // handle error redirection // ? is this even necessary ?
    if (redirect->redir == ERROR) // check if there is error redirection
    {
        fd_err = open(cmd->redir->file, O_WRONLY | O_TRUNC | O_CREAT, 0644); // if so: open error output file and save it in fd_err
        if (fd_err < 0)
            return (perror("failed to open error output file"));
    }
    else
    {
        dup2(fd_err, STDERR_FILENO); // redirect stdout to fd_err
	    close(fd_err);
    }

	// NOTE: for these simple commands, output is pipe, not a file!
	// create new pipe
	int fd_pipe[2];
	pipe(fd_pipe);
	fd_out = fd_pipe[1]; // to write
	fd_in = fd_pipe[0]; // to read !!! this makes input fd_in of the next simple command

    // redirect output:
    dup2(fd_out, 1); // redirect stdout to go to the file object pointed to by fd_out
    // now both stdin and stdout have been redirected to either a file or a pipe
    close(fd_out); // fd_out is closed as it is no longer needed
}

void set_up_pipe()
{
    int fd_pipe[2];

    if (pipe(fd_pipe) < 0)
        return (perror("Pipe failed"));

    close(fd_pipe[0]); // Close unused read end of pipe
    dup2(fd_pipe[1], STDOUT_FILENO); // Redirect stdout to write end of pipe
    close(fd_pipe[1]); // Close write end of pipe

    // CMD uitvoeren

    dup2(fd_pipe[0], STDIN_FILENO); // Redirect stdin to read end of pipe
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
	t_cmd	    *current_cmd = mini->cmd_list;
	pid_t		pid;

	while (current_cmd != NULL) // loop through linked list s_cmd made of t_cmd's:
    {
        if (current_cmd->args[0] != NULL) // check if cmd is not empty
        {
            // TODO pipe(), fd's and closing of fd's!
            if (current_cmd->next != NULL) // more than 1 cmd!
                set_up_pipe();
            if (current_cmd->redir != NULL) // check for redirect // ? WAAR MOET DIT?
                handle_redirect();
            if (builtin_check(mini->cmd_list->args[0]) == true)// check for builtin
                builtin_execute(mini->cmd_list, &mini->env_list); // execute builtin in parent
            else // if cmd is non-builtin
            {
                pid = fork(); // create child process
                if (pid < 0)
                    return (perror("fork fail"));
                if (pid == 0) // let child process execute cmd
                    non_builtin_execute();
                else
                {
                    // parent must wait for last command/ child process to finish before printing to shell prompt
                    int	status;
                    if (waitpid(pid, &status, 0) < 0)
                        return (perror("waitpid"));
                }
            }
        }
        current_cmd = current_cmd->next; // move to next node in linked list
    }
	// TODO if (WIFEXITED(status)) -> exit(WEXITSTATUS(status));
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