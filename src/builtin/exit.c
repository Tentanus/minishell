#include <minishell.h>

/*
** exit
** 
*/

int	builtin_exit(t_cmd *cmd)
{	
	ft_putstr_fd("exit\n", 2); // change fd?
	if (cmd->args[1] != NULL)
		return (ft_putstr_fd("too many arguments\n", 2), ERROR); // change fd? // minishell_error?
	else
	{
		clear_history();
		return (exit(errno), SUCCESS); // errno or our own status code?
	}
}

// exit builtin in aanvullen:
// verschil maken tussen exit voor meerdere commands vs voor één command?
// errno/exit code?
// free-en?
// SHLVL shell updaten naar -= ?