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


// !!!!!!!! NOT MY OWN CODE! WRITE OWN CODE! AND HAVE FUN DOING IT XOXOXOXO !!!!
int	ft_strlend(const char *str, char c)
{
	int	n;

	n = 0;
	if (!str)
		return (0);
	while (str[n] != '\0' && str[n] != c)
		n++;
	return (n);
}
// !!!!!!!! NOT MY OWN CODE! WRITE OWN CODE! AND HAVE FUN DOING IT XOXOXOXO !!!!
int	ft_inset(char *s1, char c)
{
	while (s1 && *s1)
	{
		if (c == *s1)
			return (1);
		s1++;
	}
	return (0);
}
// !!!!!!!! NOT MY OWN CODE! WRITE OWN CODE! AND HAVE FUN DOING IT XOXOXOXO !!!!
bool	validate_var_name(char *var)
{
	int		var_name_len;
	int		i;

	if (!ft_inset(var, '='))
		return (false);
	var_name_len = ft_strlend(var, '=');
	if (!(ft_isalpha(var[0]) || var[0] == '_'))
		return (false);
	i = 1;
	while (i < var_name_len)
	{
		if (!(ft_isalnum(var[i]) || ft_inset("+_", var[i])))
			return (false);
		i++;
	}
	return (true);
}
// !!!!!!!! NOT MY OWN CODE! WRITE OWN CODE! AND HAVE FUN DOING IT XOXOXOXO !!!!

// int		env_var_validate_name(char *name)
// {
	
// 	return (SUCCESS);
// }

// TODO export met lege variabele:
// TODO not a valid identifier VOORAL VOOR key = ? en key = $
// TODO eerste character moet isalpha zijn
// TODO daarna character moet isalphanum OF _ zijn

int	builtin_export(t_cmd *cmd, t_env_var_ll **env_var_list)
{	
	int	i;

	i = 1;
	if (cmd->args[1] == NULL) // this is the case for "export" without variables/options: that 1 arg = NULL
		builtin_export_print_export(*env_var_list);
	else
	{
		while (cmd->args[i] != NULL) 
		{
			// TODO : write validate_var_name function! SEE ABOVE
			if (validate_var_name(cmd->args[i]) == true)
				env_var_set_env(cmd->args[i], env_var_list);
			else
				minishell_export_name_error(cmd->args[i]);
			i++;
		}
	}
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