#include <minishell.h>

void    non_builtin_execute()
{
    // we are in child process
	// find paths?
    execve(path_to_cmd, cmd, envp);
    perror(“execve”);
    exit(1);
}

void handle_redirect()
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

/*
	executor() is the executing part of our minishell.
    It is fully based on the command table
    as is outputed by the lexer, parser and expander.
	For every command, redirection is handled.
    Builtin commands are executed in parent process.
    Non-builtin commands are executed in child process after forking.
*/

void	executor(t_cmd **cmd_table, t_env_var_ll **env_var_list)
{
	t_cmd	*cmd = *cmd_table;
	int		pid;

	while (cmd != NULL) // loop through linked list s_cmd made of t_cmd's:
    {
        // TODO pipe(), fd's and closing of fd's!
		if (cmd->redir != NULL) // check for redirect // ? WAAR MOET DIT?
            handle_redirect();
        if (builtin_check(cmd->cmd) == true) // check for builtin
            builtin_execute(&cmd, &env_var_list); // execute builtin in parent
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
        cmd = cmd->next; // move to next node in linked list
    }
	// TODO if (WIFEXITED(status)) -> exit(WEXITSTATUS(status));
}