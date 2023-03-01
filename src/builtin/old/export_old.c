#include <minishell.h>

/*
** export
** Export marks each name to be passed to child processes in the environment.
** If a variable name is followed by =value,
** the value of the variable is set to value.
** Export without option displays a list of names of all exported variables
** in the format 'declare -x NAME="value"'.
*/

void	print_export(char **envp)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (envp[i] != NULL)
	{
		s = envp[i];
		ft_putstr_fd("declare -x ", 1); // change 1 to fd?
		j = 0;
		while (ft_strncmp(&s[j], "=", 1) != 0)
		{
			ft_putchar_fd(s[j], 1); // change 1 to fd?
			j++;
		}
		ft_putchar_fd(s[j], 1); // change 1 to fd?
		j++;
		ft_putchar_fd('"', 1); // change 1 to fd?
		while (s[j] != '\0')
		{
			ft_putchar_fd(s[j], 1); // change 1 to fd?
			j++;
		}
		ft_putchar_fd('"', 1); // change 1 to fd?
		ft_putstr_fd("\n", 1); // change 1 to fd?
		i++;
	}
}

// char	*get_name(char	**args)
// {
// 	int		i;
// 	char	*var;
// 	char	*name;

// 	i = 0;
// 	var = args[0];
// 	printf("var = %s\n", var);
// 	while (ft_strncmp(&var[i], "=", 1) != 0)
// 		i++;
// 	ft_strlcpy(name, var, i);
// 	return (name);
// }

void	execute_export(t_cmd *cmd, t_env_var *envars)
{
	// char	*name = NULL;
	// char	*value = NULL;
	
	if (cmd->amount_of_args == 1) // this is the case for "export" without variables/options: that 1 arg = NULL
	{
		print_export(envars->our_envp);
		return ; 
	}
	// else
	// {
	// 	name = get_name(cmd->args);
	// 	value = get_value(cmd->args);
	// 	printf("name = %s\n", name);
	// 	// printf("value = %s\n", value);
	// 	set_env(name, value, envars);
	// }
}

// Notes:
// Shell variable: VARIABLE=4
// This variable is local and only available in the shell in which it is declared.
// Environment variable: export VARIABLE=4
// This variable is global, it is available in the shell's child shells, processes and commands.
// ! We can access bash environment variables only one way;
// ! the parent shell exports its variables to the child shell’s environment
// ! but the child shell can’t export variables back to the parent shell !