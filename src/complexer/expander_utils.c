/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_extra.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 14:37:00 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/08 14:37:06 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*expander_shell_var_spacer(char *str)
{
	t_token	*t_return;
	t_token	*t_node;

	t_return = NULL;
	t_node = list_token_new();
	if (!t_node)
		return (NULL);
	t_node->id = WORD;
	t_node->str = str;
	t_return = t_node;
	t_node = list_token_new();
	if (!t_node)
		return (list_token_free_node(t_return), NULL);
	t_node->id = SPACEBAR;
	t_node->str = ft_strdup(" ");
	if (!(t_node->str))
		return (list_token_free_node(t_return), \
				list_token_free_node(t_node), NULL);
	t_return->next = t_node;
	return (t_return);
}

t_token	*expander_shell_var(t_token *t_current, t_env_var_ll *env_var_list)
{
	t_token	*t_return;
	t_token	*t_node;
	char	**split;
	size_t	i;

	t_return = NULL;
	i = 0;
	split = ft_split(env_var_get_env((t_current->str + 1), env_var_list), ' ');
	if (!split)
		return (NULL);
	while (split[i] != NULL)
	{
		t_node = expander_shell_var_spacer(split[i]);
		if (!t_node)
			return (list_token_free_list(t_return, list_token_free_node_str), \
					ft_free_split(split), NULL);
		list_token_add_back(&t_return, t_node);
		i++;
	}
	free(split);
	if (i == 0)
		return (list_token_new());
	list_token_free_last(t_return, list_token_free_node_str);
	return (t_return);
}
