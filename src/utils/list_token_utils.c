/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_token_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:41:23 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/08 15:41:22 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*list_token_new(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token) * 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->id = TOKEN;
	new->str = NULL;
	return (new);
}

t_token	*list_token_last(t_token *t_list)
{
	if (t_list == NULL)
		return (NULL);
	while (t_list->next != NULL)
		t_list = t_list->next;
	return (t_list);
}

t_token	*list_token_cpy_node(t_token *t_node)
{
	t_token	*t_return;

	if (!t_node)
		return (NULL);
	t_return = list_token_new();
	if (!t_return)
		return (NULL);
	t_return->id = t_node->id;
	t_return->str = ft_strdup(t_node->str);
	if (t_return->str == NULL)
		return (free(t_return), NULL);
	t_return->next = NULL;
	return (t_return);
}

void	list_token_add_back(t_token **t_list, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	else if (!(*t_list))
	{
		*t_list = new;
		return ;
	}
	tmp = list_token_last(*t_list);
	tmp->next = new;
	return ;
}

//	NAVIGATION FUNCTIONS

t_token	*list_token_skip_space(t_token *t_current)
{
	t_token	*t_return;

	if (t_current == NULL)
		return (NULL);
	t_return = t_current->next;
	if (t_return == NULL)
		return (NULL);
	if (t_return->id == SPACEBAR)
		t_return = t_return->next;
	return (t_return);
}
