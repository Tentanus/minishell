#include <minishell.h>

/*
** this file contains function to initiate a linked linst of environment variables.
** it can be used everytime a new shell or child process is initiated.
*/

int	add_var_to_end_list()
{
	
	return (0);
}

t_env_var_ll	*init_new_var(char *env_var)
{
	t_env_var_ll 	*new_var;
	int				i;

	new_var = (t_env_var_ll *)malloc(sizeof(t_env_var_ll));
	if (!new_var)
		return (minishell_error("malloc fail init_new_var"), NULL);
	i = 0;
	while (env_var[i])
	{
		if (env_var[i] == '=')
		{
			new_var->name = ft_substr(env_var, 0, i);
			new_var->value = ft_substr(env_var, i + 1, ft_strlen(env_var));
			break ;
		}
		i++;
	}
	if (new_var->value == NULL)
		new_var->has_value = false;
	else
		new_var->has_value = true;
	new_var->next = NULL;
	return (new_var);
}

int	add_variables(char *env_var)
{
	t_env_var_ll	*new_var;

	new_var = init_new_var(env_var);
	if (!new_var)
		return (minishell_error("fail in add_variables"), 1);
	// positie van var in list?
	add_var_to_end_list(new_var);
	// of add_var_to_list();
	return (0);
}

int	init_env_var(char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i] != NULL)
	{
		if (add_variable(envp[i]) == 1);
			return (minishell_error("fail in init_env_var"), 1);
		i++;
	}
	return (0);
}

void print_linked_list(t_env_var_ll *lst)
{
    printf("list:\n");
    while(lst != NULL)
    {
        printf("%s ", lst->name);
		printf("= ");
        printf("%s ", lst->value);
        printf("%s", lst->has_value ? "true" : "false");
        lst = lst->next;
    }
    printf("\n");
}