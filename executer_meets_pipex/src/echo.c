#include "../pipex.h"

bool has_n_option(char *str)
{
    while(str)
    {
        if (ft_strncmp(str, "-n", 3) == 0)
            return(true);
        str++;
    }
    return (false);
}

int    execute_echo(t_args *arg, t_cmd *cmd)
{
    // echo [-neE] [arg …]
    // output args seperated by spaces, terminated with newline
    // returns 0 UNLESS a write error occurs
    
    // printf("%s", arg->cmd2_split[1]);

    // If -n is specified, the trailing newline is suppressed:
    // if (! -n option)
    //     put_char_fd("\n", 1);
    // :
    // ./pipex Makefile "wc" "echo -n hallo" outfile
    if (has_n_option(arg->cmd2_split[1]) == false) // zonder -n option dus met newline
    {
        printf("%s\n ", cmd->args[0]);
        printf("%s\n ", arg->cmd2_split[1]);
        // put_str_fd("\n", 1);
    }
    else // -n option dus zonder newline! ./pipex Makefile "wc" "echo hallo" outfile
        printf("%s", arg->cmd2_split[2]);
    printf("op de volgende regel?");
    return (0);
}
