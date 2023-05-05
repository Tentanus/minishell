#include <minishell.h>

/*
** exit
** 
*/

int	builtin_exit(t_cmd *cmd)
{	
	ft_putstr_fd("exit\n", 2);
	if (cmd->args[1] != NULL)
	{
		if (cmd->args[2] != NULL)
			return (mini_error_test(error_print, 1, "exit: too many arguments"), ERROR);
		if (ft_stris(cmd->args[1], ft_isdigit) == 1)
		{
			clear_history();
			return (exit(ft_atoi(cmd->args[1])), SUCCESS);
		}
		else
			return (mini_error_test(error_print, 1, "exit: numeric argument required"), exit(255), ERROR);
	}
	clear_history();
	return (exit(ft_atoi(g_status.exit_str)), SUCCESS);
}

// exit builtin in aanvullen:
// verschil maken tussen exit voor meerdere commands vs voor één command?
// errno/exit code?
// free-en?
// SHLVL shell updaten naar -= ?