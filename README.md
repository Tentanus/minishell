# minishell / marshell
#### 42/Codam project

*This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes, file descriptors, redirections and more.*

This project is a start into the world of SHELL development. The goal is to make a SHELL, losely based on bash.

### Useful Sources:
- [Readline guide](https://web.mit.edu/gnu/doc/html/rlman_2.html)
- [Readline Manual](https://man7.org/linux/man-pages/man3/readline.3.html)
- [GNU Bash Manual](www.gnu.org/savannah-checkouts/gnu/bash/manual)
- [SHELL Command Language Manual](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_03)
- [Terminal Interface](https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-Terminal-Interface.html)

### Team:
- [mverbrug](https://github.com/maresverbrugge)
- [mweverli](https://github.com/Tentanus)

<details>
<summary>Requirements</summary>

Your shell should:
- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Not use more than one global variable. Think about it. You will have to explain its purpose.
- Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
- Handle ’ (single quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence except for $ (dollar sign).
- Implement redirections:
	- '<' should redirect input.
	- '>' should redirect output.
	- '<<' should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
	- '>>' should redirect output in append mode.
- Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
- Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
- In interactive mode:
	- ctrl-C displays a new prompt on a new line.
	- ctrl-D exits the shell.
	- ctrl-\ does nothing.
- Your shell must implement the following builtins:
	- echo with option -n
	- cd with only a relative or absolute path
	- pwd with no options
	- export with no options
	- unset with no options
	- env with no options or arguments
	- exit with no options
	</details>



# MiniShell


# NOTES:

## DUP2():
dup2(old_fd, new_fd):
The dup2() function duplicates the old file descriptor to the new (standard) file descriptor,
which means that any subsequent write to the new_fd (standard output) will actually write to old_fd (the file).
if (dup2(old_fd, new_fd) == -1) // redirect from old_fd to new_fd
	return (ERROR and close(new_fd))

The close() function must close the file descriptor that was returned by open().


## Append Redirection:

// handle append redirection
``
else if (redirect->redir == APP) // check if there is append redirection
{
	fd_file = open(redirect->file, O_WRONLY | O_APPEND | O_CREAT, 0644); // if so: open outfile and save it in fd_file
	if (fd_file < 0)
		return (minishell_error("failed to open append file"));
	if (dup2(fd_file, STDOUT_FILENO) == -1) // redirect stdout to fd_file
		return (minishell_error("Dup error stdoutput < - > write end of pipe\n"));
	close(fd_file);
}
``

