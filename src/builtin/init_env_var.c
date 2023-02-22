#include <minishell.h>

/*
** this file contains function to initiate a linked linst of environment variables.
** it can be used everytime a new shell or child process is initiated.
*/

void print_linked_list(t_env_var_ll *env_var_list)
{
    printf("list:\n");
    while(env_var_list != NULL)
    {
        printf("%s ", env_var_list->name);
		printf("= ");
        printf("%s ", env_var_list->value);
        printf("%s\n", env_var_list->has_value ? "true" : "false");
        env_var_list = env_var_list->next;
    }
    printf("\n");
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

int	add_var_to_end_list(t_env_var_ll **env_var_list, t_env_var_ll *new_var)
{
	t_env_var_ll	*current = *env_var_list;

	if (*env_var_list == NULL)
		*env_var_list = new_var;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_var;
	}
	new_var->next = NULL;
	return (0);
}

int	add_variable(char *env_var, t_env_var_ll **env_var_list)
{
	t_env_var_ll	*new_var;

	new_var = init_new_var(env_var);
	if (!new_var)
		return (minishell_error("fail in add_variables"), 1);
	// positie van var in list?
	add_var_to_end_list(env_var_list, new_var);
	// print_linked_list(env_var_list);
	// of add_var_to_list();
	return (0);
}

int	init_env_var(char **envp, t_env_var_ll **env_var_list)
{
	int	i;
	
	i = 0;
	while (envp[i] != NULL)
	{
		if (add_variable(envp[i], env_var_list) == 1)
			return (minishell_error("fail in init_env_var"), 1);
		i++;
	}
	return (0);
}
