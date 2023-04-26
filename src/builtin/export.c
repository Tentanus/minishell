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

void	builtin_export_print_export(t_env_var_ll *env_var_list)
{
	while (env_var_list != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		if (env_var_list->value != NULL)
			printf("%s=\"%s\"\n", env_var_list->name, env_var_list->value);
		else
			printf("%s\n", env_var_list->name);
		env_var_list = env_var_list->next;
	}
}
// TODO export met lege variabele:
// TODO not a valid identifier VOORAL VOOR key = ? en key = $
// TODO eerste character moet isalpha zijn
// TODO daarna character moet isalphanum OF _ zijn

int	builtin_export(t_cmd *cmd, t_env_var_ll **env_var_list)
{	
	if (cmd->args[1] == NULL) // this is the case for "export" without variables/options: that 1 arg = NULL
		builtin_export_print_export(*env_var_list);
	else
		env_var_set_env(cmd->args[1], env_var_list);
	return (SUCCESS);
}


// Notes:
// Shell variable: VARIABLE=4
// This variable is local and only available in the shell in which it is declared.
// Environment variable: export VARIABLE=4
// This variable is global, it is available in the shell's child shells, processes and commands.
// We can access bash environment variables only one way;
// the parent shell exports its variables to the child shell’s environment
// but the child shell can’t export variables back to the parent shell !