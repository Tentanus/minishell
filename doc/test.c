// void execute()
// {
//     int i = 0;
//     int pid;
//     int number_of_commands;
//     while (i < number_of_commands)
//     {
//         pid = fork();
//         if (pid < 0)
//         {
//             perror("fork fail"); 
//             return ;
//         }
//         if (pid == 0) // child process
//         {
//             execve(path_to_cmd, cmd, envp); 
//             perror(“execve”);
//             exit(1);
//         }
//         // Parent process
//         i++;
//     }
//     //  wait for last command/process to finish
//     // only if & (background) was not set
//     if (!background)
//         waitpid(pid, NULL);
// }

// void redirect_and_execute_cmd()
// {
//     // PARENT
//     // stdin and stdout (fd 0 and 1) will be modified in the parent 
//     // during the execution of the simple commands
//     // store current stdin and stdout into two new fds using dup():
//     int fd_in_tmp = dup(0);
//     int fd_out_tmp = dup(1);

//     // set initial input:
//     int fd_in;
//     // check if there is input redirection
//     if (infile)
//         fd_in = open(infile, O_RDONLY); // if so: open infile and save it in fd_in
//     else
//         fd_in = dup(fd_in_tmp); // if not: create fd_in that points to default input
//     // fd_in will now be file descriptor that has the input of the command line
//     // it can be closed without affecting the parent shell program

//     // iterate over simple commands in command table
//     // create new process for every simple command
//     // perform pipe connections
//     int i = 0;
//     int fd_out;
//     int number_of_commands;
//     while (i < number_of_commands)
//     {
//         dup2(fd_in, 0); // redirect standard input to come from fd_in:
//         // any read from stdin will come from file pointed to by fd_in.
//         close(fd_in);
//         if (i == number_of_commands - 1) // if last command:
//         {
//             // check if there is a output file redirection like command > outfile
//             if (outfile)
//                 fd_out = open(outfile); // if so: open outfile and save it in fd_out
//             else
//                 fd_out = dup(fd_out_tmp); // if not: create fd_out that points to default output
//         }
//         else // for every command that is not the last command:
//         { // NOTE: for these simple commands, output is pipe, not a file!
//             // create new pipe
//             int fd_pipe[2];
//             pipe(fd_pipe);
//             fd_out = fd_pipe[1]; // to write
//             fd_in = fd_pipe[0]; // to read !!! this makes input fd_in of the next simple command
//             // in the next iteration to come from fd_pipe[0] of the current simple command
//         }
//         // redirect output:
//         dup2(fd_out, 1); // redirect stdout to go to the file object pointed to by fd_out
//         // now both stdin and stdout have been redirected to either a file or a pipe
//         close(fd_out); // fd_out is closed as it is no longer needed

//         // create child process and execute (code below OR see execute() function above):
//         // note that input and output redirections for current command are already set
//         int pid = fork(); // child process inherits redirected fds
//         if (pid < 0)
//             // throw error and return;
//         if (pid == 0) // child process
//         {
//             execve(path_to_cmd, cmd, envp);
//             handle execve fail: error message and exit();
//         }

//         i++; // iterate over cmds in command table
//     }

//     // restore defaults for input and output for parent
//     dup2(fd_in_tmp, 0);
//     dup2(fd_out_tmp, 1);
//     // close temorary fds
//     close(fd_in_tmp);
//     close(fd_out_tmp);

//     // only if & (background) character is not set
//     // parent must wait for last command/ child process to finish before printing to shell prompt
//     if (!background)
//         waitpid(pid, NULL);

//     // * still need to set up stderror redirection (fd 2). 
//     // * make sure that stderr of ALL simple commands will be send to the same place!

//     // Built-in functions in parent process
//     // Call built-in function in executor instead of forking.
// }