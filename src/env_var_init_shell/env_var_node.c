#include <minishell.h>

/*
* function to create a new env node that has all values set to NULL
*/
t_env_var_ll	*env_var_init_node(void)
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
** function that creates a new node containing environment
** variable in format of NAME=value
** also adds bool with 'has value' = true or false for every node.
*/
t_env_var_ll	*env_var_create_new_node(char *env_var_str)
{
	t_env_var_ll	*new_env_node;
	int				i;

	if (!env_var_str)
		return (NULL);
	new_env_node = env_var_init_node();
	if (!new_env_node)
		return (mini_error_test(error_print, 1, \
			"(malloc) fail in initiating new_env_node"), NULL);
	i = 0;
	while (env_var_str[i] && env_var_str[i] != '=')
		i++;
	new_env_node->name = ft_substr(env_var_str, 0, i);
	if (new_env_node->name == NULL)
		return (env_var_free_node(new_env_node), NULL);
	if (env_var_str[i] == '\0')
		return (new_env_node);
	new_env_node->value = ft_substr(env_var_str, i + 1, \
		ft_strlen(env_var_str + i + 1));
	if (new_env_node->value == NULL)
		return (env_var_free_node(new_env_node), NULL);
	new_env_node->has_value = true;
	return (new_env_node);
}

t_env_var_ll	*env_var_get_env_node(char *name, t_env_var_ll *env_var_list)
{
	t_env_var_ll	*current_node;
	int				len_name;

	if (!name || !env_var_list)
		return (NULL);
	len_name = ft_strlen(name) + 1;
	current_node = env_var_list;
	while (current_node != NULL)
	{
		if (ft_strncmp(current_node->name, name, len_name) == 0)
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}

/*
** function to free content and node in env_var_list
*/
void	env_var_free_node(t_env_var_ll *env_var_node)
{
	free(env_var_node->name);
	if (env_var_node->value)
		free(env_var_node->value);
	free(env_var_node);
}
