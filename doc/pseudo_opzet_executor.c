

void    execute_cmd()
{
    // we are in child process
    execve(path_to_cmd, cmd, envp);
    perror(“execve”);
    exit(1);
}

void    handle_pipe()
{
   	int	fd_pipe[2];
    
    if (pipe(fd_pipe) == -1)
        exit_message("Pipe failed\n", 1);
}

void handle_redirect()
{
    // PARENT
    // stdin and stdout (fd 0 and 1) will be modified in the parent 
    // during the execution of the simple commands
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

    // iterate over simple commands in command table
    // create new process for every simple command
    // perform pipe connections
    int i = 0;
    int fd_out;
    int number_of_commands;
    while (i < number_of_commands)
    {
        dup2(fd_in, 0); // redirect standard input to come from fd_in:
        // any read from stdin will come from file pointed to by fd_in.
        close(fd_in);
        if (i == number_of_commands - 1) // if last command:
        {
            // check if there is a output file redirection like command > outfile
            if (outfile)
                fd_out = open(outfile); // if so: open outfile and save it in fd_out
            else
                fd_out = dup(fd_out_tmp); // if not: create fd_out that points to default output
        }
        else // for every command that is not the last command:
        { // NOTE: for these simple commands, output is pipe, not a file!
            // create new pipe
            int fd_pipe[2];
            pipe(fd_pipe);
            fd_out = fd_pipe[1]; // to write
            fd_in = fd_pipe[0]; // to read !!! this makes input fd_in of the next simple command
            // in the next iteration to come from fd_pipe[0] of the current simple command
        }
        // redirect output:
        dup2(fd_out, 1); // redirect stdout to go to the file object pointed to by fd_out
        // now both stdin and stdout have been redirected to either a file or a pipe
        close(fd_out); // fd_out is closed as it is no longer needed

        // ? HERE execute cmd?
    }

    // restore defaults for input and output for parent
    dup2(fd_in_tmp, 0);
    dup2(fd_out_tmp, 1);
    // close temorary fds
    close(fd_in_tmp);
    close(fd_out_tmp);

    // only if & (background) character is not set
    // parent must wait for last command/ child process to finish before printing to shell prompt
    if (!background)
        waitpid(pid, NULL);


    // * still need to set up stderror redirection (fd 2). 
    // * make sure that stderr of ALL simple commands will be send to the same place!
}

/*
	executor() is the executing part of our minishell.
    It is fully based on the command table
    as is outputed by the lexer, parser and expander.
    Builtin commands are executed in parent process.
    Non-builtin commands are executed in child process after forking.
*/

void    executor()
{
    while (cmd != NULL) // loop through linked list s_cmd made of t_cmd's:
    {
        if (cmd.redir != NULL) // check for redirect // ? WAAR MOET DIT?
            handle_redirect();
        if (cmd.next != NULL) // check for pipes
            handle_pipe(); // create pipe to connect input and output of cmds
        if (builtin_check(cmd.cmd) == true) // check for builtin
            builtin_execute(&cmd, &env_var_list); // execute builtin in parent
        else // if cmd is not a builtin
        {
            pid = fork(); // create child process
            if (pid < 0)
                return (perror("fork fail"));
            if (pid == 0) // let child process execute cmd
                execute_cmd();
        }
        cmd = cmd->next; // move to next node in linked list
    }
}

int	main(int argc, char **argv, char **envp)
{
	t_env_var_ll	*env_var_list = NULL;
	t_cmd		    cmd;
	char		    *input;
	(void) argc; // to silence compiler
	(void) argv; // to silence compiler
	(void) envp; // to silence compiler
    int             pid;

	if (init_shell(envp, &env_var_list) == 1)
		return (1);

	input = NULL;
	while (1)
	{
		input = readline(prompt);
		mini_parse_input(input, &cmd);
        executor();
		free(input);
	}
	return (0);
}
