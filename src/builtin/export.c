#include <minishell.h>

/*
** export
** Export marks each name to be passed to child processes in the environment.
** If a variable name is followed by =value,
** the value of the variable is set to value.
** Export without option displays a list of names of all exported variables
** in the format 'declare -x NAME="value"'.
*/

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

int	ft_strlen_char(const char *str, char c)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0' && str[len] != c)
		len++;
	return (len);
}

/*
** env_var_validate_name
** first character of "name" should be alphabetic (isalpha) or underscore "_"
** rest of characters of "name" should be alphabetic
** or numeric (isalnum) or "_" underscore
*/
bool	env_var_validate_name(char *name)
{
	int		name_len;
	int		i;

	name_len = ft_strlen_char(name, '=');
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 0;
	while (i < name_len)
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	env_var_validate_args(char *name, t_env_var_ll **env_var_list)
{
	char	*name_tmp;
	int		i;

	i = 0;
	if (!name)
		return (ERROR);
	while (name[i] && name[i] != '=')
		i++;
	name_tmp = ft_substr(name, 0, i);
	if (!name_tmp)
		return (ERROR);
	if (env_var_exists(name_tmp, *env_var_list) == true)
	{
		if (ft_strncmp(name_tmp, "_", 2) == 0)
			return (free(name_tmp), mini_error(export_error, 1, name), ERROR);
		if (ft_strchr(name, '=') == 0)
			return (free(name_tmp), SUCCESS);
		else
			return (free(name_tmp), env_var_set_env(name, env_var_list), SUCCESS);
	}
	if (env_var_validate_name(name) == true)
		env_var_set_env(name, env_var_list);
	else
		return (free(name_tmp), mini_error(export_error, 1, name), ERROR);
	return (free(name_tmp), SUCCESS);
}

int	builtin_export(t_cmd *cmd, t_env_var_ll **env_var_list)
{	
	int	i;

	i = 1;
	if (cmd->args[i] == NULL)
		builtin_export_print_export(*env_var_list);
	else
	{
		while (cmd->args[i] != NULL)
		{
			if (env_var_validate_args(cmd->args[i], env_var_list) == ERROR)
				status_update(1);
			i++;
		}
	}
	if (ft_strncmp(g_status.exit_str, "1", 2) == 0)
		return (ERROR);
	return (SUCCESS);
}

// Notes:
// Shell variable: VARIABLE=4
// This variable is local and only available in the shell
// in which it is declared.
// Environment variable: export VARIABLE=4
// This variable is global, it is available in the 
// shell's child shells, processes and commands.
// We can access bash environment variables only one way;
// the parent shell exports its variables to the child shell’s environment
// but the child shell can’t export variables back to the parent shell !

// according to POSIX.1-2017, a value is added to the existing string if a user
// enters name+=value
// our shell does not handle this, instead it gives the error message
// "not a valid identifier"
