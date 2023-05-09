/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var_list.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:26:57 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/09 11:41:14 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** function that adds a new node containing a new
** environment variable in format of NAME=value
** to the end of the linked list of environment variables.
*/
void	list_env_var_add_back(t_env_var_ll **env_var_list, \
	t_env_var_ll *new_env_var)
{
	t_env_var_ll	*current;

	if (env_var_list == NULL || new_env_var == NULL)
		return ;
	if (*env_var_list == NULL)
	{
		*env_var_list = new_env_var;
		return ;
	}
	current = *env_var_list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_env_var;
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

	if (!env_node || !env_node->name)
		return (NULL);
	ret = ft_calloc(sizeof(char), (ft_strlen(env_node->name) + \
				ft_strlen(env_node->value) + 2));
	if (!ret)
		return (NULL);
	ft_strlcat(ret, env_node->name, ft_strlen(env_node->name) + 1);
	ft_strlcat(ret, "=", ft_strlen(ret) + 2);
	ft_strlcat(ret, env_node->value, \
		ft_strlen(ret) + ft_strlen(env_node->value) + 1);
	return (ret);
}

char	**list_env_var_convert_to_cpp(t_env_var_ll *env_list)
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

/*
** function to free whole of env_var_list
*/
void	list_env_var_free_list(t_env_var_ll *env_var_list)
{
	t_env_var_ll	*tmp_env;

	if (env_var_list == NULL)
		return ;
	while (env_var_list)
	{
		tmp_env = env_var_list->next;
		list_env_var_free_node(env_var_list);
		env_var_list = tmp_env;
	}
}
