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
	int i;
	int j;
	char *s;
    
    i = 0;
	while(envp[i] != NULL)
	{
		s = envp[i];
		ft_putstr_fd("declare -x ", 1); // change 1 to fd?
		j = 0;
		while(ft_strncmp(&s[j], "=", 1) != 0)
		{
			ft_putchar_fd(s[j], 1); // change 1 to fd?
			j++;
		}
		ft_putchar_fd(s[j], 1); // change 1 to fd?
		j++;
		ft_putchar_fd('"', 1); // change 1 to fd?
		while(s[j] != '\0')
		{
			ft_putchar_fd(s[j], 1); // change 1 to fd?
			j++;
		}
		ft_putchar_fd('"', 1); // change 1 to fd?
		ft_putstr_fd("\n", 1); // change 1 to fd?
		i++;
	}
	// if (i == 0)
	// 	ft_putstr_fd("(null)\n", 1); // change 1 to fd?
    return ;
}

void	execute_export(char **envp)
{
	print_export(envp);
	
}


// Notes:
// Shell variable: VARIABLE=4
// This variable is local and only available in the shell in which it is declared.
// Environment variable: export VARIABLE=4
// This variable is global, it is available in the shell's child shells, processes and commands.
// ! We can access bash environment variables only one way;
// ! the parent shell exports its variables to the child shell’s environment
// ! but the child shell can’t export variables back to the parent shell !