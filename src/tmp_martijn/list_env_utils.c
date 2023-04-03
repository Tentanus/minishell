#include <minishell.h>

/*
** function to free content and node in env_var_list
*/
//void	env_var_free_node(t_env_var_ll *env_var_list)
void	list_env_free_node(t_env_var_ll *env_node)
{
	char	*tmp;

	tmp = env_node->name;
	env_node->name = NULL;
	free(tmp);
	tmp = env_node->value;
	env_node->value = NULL;
	free(tmp);
	free(env_node);
}

void	list_env_free_list(t_env_var_ll *env_list)
{
	t_env_var_ll	*env_tmp;

	if (env_list == NULL)
		return ;
	while (env_list)
	{
		env_tmp = env_list->next;
		list_env_free_node(env_list);
		env_list = env_tmp;
	}
	return ;
}

t_env_var_ll	*list_env_get_node(char *name, t_env_var_ll *env_list)
{
	size_t	len_name;

	if (!name || !env_list)
		return (NULL);
	len_name = ft_strlen(name) + 1;
	while (env_list != NULL)
	{
		if (ft_strncmp(env_list->name, name, len_name) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

/*
 * fucntion to create a new env node that has all values set to NULL
 */
t_env_var_ll	*list_env_new(void)
{
	t_env_var_ll	*env_node;

	env_node = malloc(sizeof(t_env_var_ll));
	if (!env_node)
		return (NULL);
	env_node->name = NULL;
	env_node->value = NULL;
	env_node->has_value = false;
	env_node->next = NULL;
	return (env_node);
}

/*
** function that creates a new node containing environment variable in format of NAME=value
** also adds bool with 'has value' = true or false for every node.
*/
//t_env_var_ll	*env_var_init_new_var_node(char *env_var)
t_env_var_ll	*list_env_fill_new(char *env_str)
{
	t_env_var_ll	*env_node;
	size_t			i;

	if (!env_str)
		return (NULL);
	env_node = list_env_new();
	if (!env_node)
		return (NULL);
	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	env_node->name = ft_substr(env_str, 0, i);
	if (env_node->name == NULL)
		return (list_env_free_node(env_node), NULL);
	if (env_str[i] == '\0')
	{
		env_node->has_value = false;
		return (env_node);
	}
	env_node->value = ft_substr(env_str, i + 1, ft_strlen(env_str + i + 1));
	if (env_node->value == NULL)
		return (list_env_free_node(env_node), NULL);
	env_node->has_value = true;
	return (env_node);
}

/*
** function that adds a new node containing a new environment variable in format of NAME=value
** to the end of the linked list of environment variables.
*/
//int	env_var_add_to_end_list(t_env_var_ll **env_var_list, t_env_var_ll *new_var)
int	list_env_add_back(t_env_var_ll **env_list, t_env_var_ll *env_node)
//why does this fucntion return an int?
{
	t_env_var_ll	*current;

	if (env_list == NULL || env_node == NULL) // can segfault if no list is given
		return (1);
	if (*env_list == NULL)
	{
		*env_list = env_node;
		return (0);
	}
	current = *env_list;
	while (current->next != NULL)
		current = current->next;
	current->next = env_node;
	env_node->next = NULL; // could be removed if propperly implemented.
	return (0);
}

//size_t	env_var_size_has_value(t_env_var_ll *env_list)
size_t	list_env_size(t_env_var_ll *env_list)
{
	size_t	ret_size;

	if (env_list == NULL)
		return (0);
	ret_size = 0;
	while (env_list != NULL)
	{
		if (env_list->has_value)
			ret_size++;
		env_list = env_list->next;
	}
	return (ret_size);
}

//char	*env_var_make_cp(const t_env_var_ll *env_node)
char	*list_env_convert_node_str(const t_env_var_ll *env_node)
{
	char	*ret;

	if (!env_node)
		return (NULL);
	ret = ft_calloc(sizeof(char), (ft_strlen(env_node->name) + \
				ft_strlen(env_node->value) + 2));
	if (!ret)
		return (NULL);
	ft_strlcat(ret, env_node->name, ft_strlen(env_node->name) + 1);
	ft_strlcat(ret, "=", ft_strlen(ret) + 2);
	ft_strlcat(ret, env_node->value, ft_strlen(ret) + ft_strlen(env_node->value) + 1);
	return (ret);
}

//char	**env_var_to_cpp(t_env_var_ll *env_list)
char	**list_env_convert_list_cpp(t_env_var_ll *env_list)
{
	t_env_var_ll	*env_current;
	char			**env_ret;
	size_t			i;

	env_current = env_list;
	env_ret = ft_calloc(sizeof(char *), (list_env_size(env_list) + 1));
	if (!env_ret)
		return (NULL);
	i = 0;
	while (env_current != NULL)
	{
		if (env_current->has_value)
		{
			env_ret[i] = list_env_convert_node_str(env_current);
			i++;
		}
		env_current = env_current->next;
	}
	return (env_ret);
}
