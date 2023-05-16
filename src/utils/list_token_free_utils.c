/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_token_free_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 15:38:31 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/16 15:04:53 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*list_token_free_node_str(t_token *t_node)
{
	t_token	*t_tmp;

	t_tmp = t_node->next;
	if (t_node == NULL)
		return (NULL);
	if (t_node->str != NULL)
		free(t_node->str);
	t_node->str = NULL;
	free(t_node);
	return (t_tmp);
}

t_token	*list_token_free_node_non_word(t_token *t_node)
{
	t_token	*t_tmp;

	t_tmp = t_node->next;
	if (t_node == NULL)
		return (NULL);
	if (t_node->id != WORD && \
	t_node->id != QUOTE && \
	t_node->id != DQUOTE)
		free(t_node->str);
	free(t_node);
	return (t_tmp);
}

t_token	*list_token_free_node(t_token *t_node)
{
	t_token	*t_tmp;

	t_tmp = t_node->next;
	if (t_node == NULL)
		return (NULL);
	free(t_node);
	return (t_tmp);
}

void	list_token_free_last(t_token *t_list, t_token *(*f) (t_token *))
{
	t_token	*t_previous;

	if (t_list == NULL)
		return ;
	while (t_list->next != NULL)
	{
		t_previous = t_list;
		t_list = t_list->next;
	}
	t_previous->next = f(t_list);
}

void	list_token_free_list(t_token *t_list, t_token *(*f) (t_token *))
{
	if (t_list == NULL)
		return ;
	while (t_list != NULL)
		t_list = f(t_list);
	return ;
}
