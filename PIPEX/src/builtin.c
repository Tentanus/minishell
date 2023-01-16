#include "../pipex.h"

bool    check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
        return(true);
    if (ft_strncmp(cmd, "cd", 3) == 0)
        return(true);
    if (ft_strncmp(cmd, "pwd", 4) == 0)
        return(true);
    if (ft_strncmp(cmd, "export", 8) == 0)
        return(true);
    if (ft_strncmp(cmd, "unset", 7) == 0)
        return(true);
    if (ft_strncmp(cmd, "env", 4) == 0)
        return(true);
    if (ft_strncmp(cmd, "exit", 5) == 0)
        return(true);
    return (false);
}

void    execute_builtin(char *str)
{
    if (ft_strncmp(arg->cmd2_split[1], "echo", 4) == 0)
        execute_echo(cmd);
    // if (ft_strncmp(cmd, "cd", 3) == 0)
    //     return(true);
    // if (ft_strncmp(cmd, "pwd", 4) == 0)
    //     return(true);
    // if (ft_strncmp(cmd, "export", 8) == 0)
    //     return(true);
    // if (ft_strncmp(cmd, "unset", 7) == 0)
    //     return(true);
    // if (ft_strncmp(cmd, "env", 4) == 0)
    //     return(true);
    // if (ft_strncmp(cmd, "exit", 5) == 0)
    //     return(true);
    return (false);
}

void    our_echo(char *str)
{
    printf("%s\n", str);
}