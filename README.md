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

Bouw image genaamd ubuntu-c-dev op basis van Dockerfile:
```bash
docker build -t ubuntu-c-dev .
```

Draai container op basis van image genaamd  ubuntu-c-dev met mounted eigen folder:
```bash
docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -it --rm --init -v "$PWD:/pwd"  ubuntu-c-dev sh -c "cd /pwd; bash"
```
--cap-add=SYS_PTRACE --security-opt seccomp=unconfined = nodig om lldb te kunnen runnen in container
-i = interactive so bash doesn't immediately quit because there is no input\
-t = bash shows prompt\
--rm = delete container on exit to not waste space\
-v = mounts specific folder from host to Docker container\
--init = shiieet snap het nut niet, maar Noah gebruikt het\
-c = CPU shares (relative weight) ???\
sh = ?

Run code met readline in Ubuntu:
```bash
gcc code.c -L/usr/local/lib -I/usr/local/include -lreadline
```