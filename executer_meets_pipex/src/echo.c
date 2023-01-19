// #include "../pipex.h"

typedef struct s_cmd
{
	char 			*simple_cmd;
	char 			**args;
    int             amount_of_args;
	struct s_cmd	*next;
}				t_cmd;

#include <stdio.h> // for printf
#include <stdbool.h> // for bool
#include <unistd.h> // for write
#include <stdlib.h> // for malloc

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return ;
}

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (s)
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
	return ;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

bool    check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
        return(true);
    return (false);
}

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

int    execute_echo(t_cmd *cmd)
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
        ft_putstr_fd(cmd->args[i], 1);
        if (i != (cmd->amount_of_args - 1))
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (n_option == 0)
        ft_putchar_fd('\n', 1);
    return (0);
}

void    execute_builtin(t_cmd *cmd)
{
    if (ft_strncmp(cmd->simple_cmd, "echo", 5) == 0)
        execute_echo(cmd);
}

char	**ft_make_array(int word_count)
{
	char	**result;

	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

void	parse_input(int argc, char **argv, t_cmd *cmd)
{
	cmd->simple_cmd = argv[1];
    // printf("%s\n", cmd->simple_cmd);
    cmd->amount_of_args = argc - 2;
    cmd->args = ft_make_array(cmd->amount_of_args);
	int i = 2;
    int j = 0;
    while (i < argc)
    {
        cmd->args[j] = argv[i];
        j++;
        i++;
    }
    cmd->args[j] = NULL;
    return ;
}

int	main(int argc, char **argv)
{
	t_cmd cmd;
    
    parse_input(argc, argv, &cmd);
    if (check_builtin(cmd.simple_cmd) == true)
        execute_builtin(&cmd);
	return (0);
}
