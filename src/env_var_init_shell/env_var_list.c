#include <minishell.h>

/*
** print linked list of environment variables FOR TESTING!
*/
void	print_linked_list(t_env_var_ll *env_var_list)
{
	printf("LINKED LISTOF ENV VARS:\n\n");
	while (env_var_list != NULL)
	{
		printf("%s ", env_var_list->name);
		printf("= ");
		printf("%s ", env_var_list->value);
		printf("%s\n", env_var_list->has_value ? "true" : "false");
		env_var_list = env_var_list->next;
	}
	printf("\n\n");
}

/*
** function to free content and node in env_var_list
*/
void	env_var_free_node(t_env_var_ll *env_var_list)
{
	free(env_var_list->name);
	free(env_var_list->value);
	free(env_var_list);
}

/*
** function that creates a new node containing environment variable in format of NAME=value
** also adds bool with 'has value' = true or false for every node.
*/
t_env_var_ll	*env_var_init_new_var_node(char *env_var)
{
	t_env_var_ll	*new_var;
	int				i;

	new_var = (t_env_var_ll *)malloc(sizeof(t_env_var_ll));
	if (!new_var)
		return (minishell_error("malloc fail init_new_var"), NULL);
	i = 0;
	if (ft_strchr(env_var, '=') != NULL) 
	{
		while (env_var[i])
		{
			if (env_var[i] == '=')
			{
				new_var->name = ft_substr(env_var, 0, i);
				new_var->value = ft_substr(env_var, i + 1, ft_strlen(env_var) - i - 1);
				break ;
			}
			i++;
		}
		new_var->has_value = true;
	}
	else
	{
		new_var->name = env_var;
		new_var->value = NULL;
		new_var->has_value = false;
	}
	new_var->next = NULL;
	return (new_var);
}

/*
** function that adds a new node containing a new environment variable in format of NAME=value
** to the end of the linked list of environment variables.
*/
int	env_var_add_to_end_list(t_env_var_ll **env_var_list, t_env_var_ll *new_var)
{
	t_env_var_ll	*current;

	current = *env_var_list;
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