#include <minishell.h>

bool is_n_option(char *str)
{
    if (ft_strncmp(str, "-n", 2) == 0)
    {
        int i = 2;
        int len = ft_strlen(str);
        while (i < len)
        {
            if (ft_strncmp(str + i, "n", 1) != 0)
                return (false);
            i++;
        }
        return(true);
        // printf("testje\n");
        // printf("str = %s\n", str);
        // printf("str + i = %s\n", str + i);
    }
    else
        return (false);
}

int    execute_echo(t_cmd *cmd, int fd)
{
    // echo [-neE] [arg …]
    // output args seperated by spaces, terminated with newline
    // returns 0 UNLESS a write error occurs
    int i = 0;
    int n_option = 0;
    while (is_n_option(cmd->args[i]) == true)
    {
        n_option = 1;
        i++;
    }
    while (i < cmd->amount_of_args)
    {
        ft_putstr_fd(cmd->args[i], fd);
        if (i != (cmd->amount_of_args - 1))
            ft_putchar_fd(' ', fd);
        i++;
    }
    if (n_option == 0)
        ft_putchar_fd('\n', fd);
    return (0);
}
