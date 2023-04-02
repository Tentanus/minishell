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
	char	*tmp;

	tmp = env_var_list->name;
	env_var_list->name = NULL;
	free(tmp);
	tmp = env_var_list->value;
	env_var_list->value = NULL;
	free(tmp);
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

size_t	env_var_size_has_value(t_env_var_ll *env_list)
{
	size_t	ret_size;

	ret_size = 0;
	while (env_list != NULL)
	{
		if (env_list->has_value)
			ret_size++;
		env_list = env_list->next;
	}
	return (ret_size);
}

char	*env_var_make_cp(const t_env_var_ll *env_node)
{
	char	*ret;

	ret = ft_calloc(sizeof(char), (ft_strlen(env_node->name) + \
				ft_strlen(env_node->value) + 2));
	ft_strlcat(ret, env_node->name, ft_strlen(env_node->name) + 1);
	ft_strlcat(ret, "=", ft_strlen(ret) + 2);
	ft_strlcat(ret, env_node->value, ft_strlen(ret) + ft_strlen(env_node->value) + 1);
	return (ret);
}

char	**env_var_to_cpp(t_env_var_ll *env_list)
{
	t_env_var_ll	*env_current;
	char			**env_ret;
	size_t			i;

	env_current = env_list;
	env_ret = ft_calloc(sizeof(char *), (env_var_size_has_value(env_list) + 1));
	if (!env_ret)
		return (NULL);
	i = 0;
	while (env_current != NULL)
	{
		if (env_current->has_value)
		{
			env_ret[i] = env_var_make_cp(env_current);
			i++;
		}
		env_current = env_current->next;
	}
	return (env_ret);
}