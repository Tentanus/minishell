#include <minishell.h>

/*
** export
** Export marks each name to be passed to child processes in the environment.
** If a variable name is followed by =value,
** the value of the variable is set to value.
** Export without option displays a list of names of all exported variables
** in the format 'declare -x NAME="value"'.
*/

// function to export variable (export)

void	print_export(t_env_var_ll *env_var_list)
{
	while (env_var_list != NULL)
	{
		ft_putstr_fd("declare -x ", 1); // change 1 to fd?
		if (env_var_list->value != NULL)
			printf("%s=\"%s\"\n", env_var_list->name, env_var_list->value);
		else
			printf("%s\n", env_var_list->name);
		env_var_list = env_var_list->next;
	}
}

void	execute_export(t_cmd *cmd, t_env_var_ll **env_var_list)
{	
	if (cmd->amount_of_args == 1) // this is the case for "export" without variables/options: that 1 arg = NULL
		print_export(*env_var_list);
	else
		set_env(cmd->args[0], env_var_list);
}

// Notes:
// Shell variable: VARIABLE=4
// This variable is local and only available in the shell in which it is declared.
// Environment variable: export VARIABLE=4
// This variable is global, it is available in the shell's child shells, processes and commands.
// We can access bash environment variables only one way;
// the parent shell exports its variables to the child shell’s environment
// but the child shell can’t export variables back to the parent shell !