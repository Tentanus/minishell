#include <minishell.h>

/*
** our own env function: it prints all environment variables (env builtin)
*/

// function to print environment variables stored in linked list (env builtin)
int	builtin_env(t_env_var_ll *env_var_list)
{
	while (env_var_list != NULL)
	{
		if (env_var_list->has_value == true)
		{
			printf("%s", env_var_list->name);
			printf("=");
			printf("%s", env_var_list->value);
			printf("\n");
		}
		env_var_list = env_var_list->next;
	}
	return (SUCCESS);
}

int	NEW_builtin_env(t_env_var_ll *env_var_list)
{
	while (env_var_list != NULL)
	{
		if (env_var_list->has_value == true)
		{
			ft_putstr_fd(env_var_list->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env_var_list->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env_var_list = env_var_list->next;
	}
	return (SUCCESS);
}