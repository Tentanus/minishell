#include <minishell.h>

/*
** exit
** 
*/

void	execute_exit(t_cmd *cmd)
{	
	if (cmd->amount_of_args > 1)
		ft_putstr_fd("too many arguments\n", 1); // change fd? // minishell_error?
	else
	{
		ft_putstr_fd("exit\n", 1); // change fd?
		exit(errno);
	}
}
