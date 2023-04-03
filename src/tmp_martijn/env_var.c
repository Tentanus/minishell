#include <minishell.h>

/*
** our own getenv function:
** the NAME of the environment variable is search in env_var_list
** if env_var exists, it's VALUE is returned
*/
//char	*env_var_get_env(char *name, t_env_var_ll *env_var_list)
char	*env_var_getenv(char *name, t_env_var_ll *env_var_list)
{
	size_t	len_name;

	len_name = ft_strlen(name) + 1;
	while (env_var_list != NULL)
	{
		if (ft_strncmp(env_var_list->name, name, len_name) == 0)
			return (env_var_list->value);
		env_var_list = env_var_list->next;
	}
	return (NULL);
}

/*
** our own setenv() function: it sets a (new) environment variable
*/
//void	env_var_set_env(char *envar, t_env_var_ll **env_var_list)
void	env_var_setenv(char *envar, t_env_var_ll **env_var_list)
{
	size_t			len_name;
	t_env_var_ll	*env_node;
	t_env_var_ll	*env_current;
	t_env_var_ll	*prev;

	if (!envar || env_var_list)
		return ;
	prev = NULL;
	env_current = *env_var_list;
	env_node = list_env_fill_new(envar);
	len_name = ft_strlen(env_node->name) + 1;
	while (env_current != NULL)
	{
		if (ft_strncmp(env_current->name, env_node->name, len_name) == 0)
		{
			env_node->next = env_current->next;
			if (prev == NULL)
				*env_var_list = env_node;
			else
				prev->next = env_node;
			env_var_free_node(env_current);
			return ;
		}
		prev = env_current;
		env_current = env_current->next;
	}
	env_var_add_to_end_list(env_var_list, env_node);
}
