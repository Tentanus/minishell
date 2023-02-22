#include <minishell.h>

/*
** this file contains function to initiate a linked linst of environment variables.
** it can be used everytime a new shell or child process is initiated.
*/

t_env_var_ll	*init_new_var(char *env_var)
{
	t_env_var_ll 	*new_var;
	int	i;

	new_var = (t_env_var_ll *)malloc(sizeof(t_env_var_ll));
	if (!new_var)
		return (minishell_error("malloc fail init_new_var"), NULL);
	i = 0;
	while (env_var[i])
	{
		if (env_var[i] == '=')
		{
			new_var->name = ft_substr(env_var, 0, i);
			i++;
			new_var->value = ft_substr(env_var, i, ft_strlen(env_var));
		}
		i++;
	}
	if (new_var->value != NULL)
		new_var->has_value = true;
	else
		new_var->has_value = false;
	new_var->next = NULL;
	return (new_var);
}

int	add_variables(char *env_var)
{
	t_env_var_ll	*new_var;

	new_var = init_new_var(env_var);
	if (!new_var)
		return (minishell_error("fail in add_variables"), NULL);
	// positie van var in list?
	// add_var_to_end_of_list? of add_var_to_list();
	return (0);
}

int	init_env_var(char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i] != NULL)
	{
		add_variable(envp[i]);
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