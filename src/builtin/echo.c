#include <minishell.h>

/*
** echo:
** echo [-n] [arg …]
** Outputs the args, separated by spaces, terminated with a newline. 
** The return status is 0 unless a write error occurs. 
** If -n is specified, the trailing newline is suppressed.
*/

bool	builtin_echo_is_n_option(char *str)
{
	int	i;
	int	len;

	if (ft_strncmp(str, "-n", 2) == 0)
	{
		i = 2;
		len = ft_strlen(str);
		while (i < len)
		{
			if (ft_strncmp(str + i, "n", 1) != 0)
				return (false);
			i++;
		}
		return (true);
	}
	else
		return (false);
}

int		builtin_echo(t_cmd *cmd, int fd)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	// fix seg fault for 'echo -n' command without other args
	while (builtin_echo_is_n_option(cmd->args[i]) == true)
	{
		n_option = 1;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		ft_putstr_fd(cmd->args[i], fd);
		if (cmd->args[i + 1] != NULL)
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (n_option == 0)
		ft_putchar_fd('\n', fd);
	return (1);
}
