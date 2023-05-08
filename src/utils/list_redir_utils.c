/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_redir_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:41:18 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/08 13:41:19 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir	*list_redir_new(void)
{
	t_redir	*redir_node;

	redir_node = malloc(sizeof(t_redir) * 1);
	if (!redir_node)
		return (NULL);
	redir_node->redir = REDIR;
	redir_node->file = NULL;
	redir_node->fd = -1;
	redir_node->next = NULL;
	return (redir_node);
}

t_redir	*list_redir_last(t_redir *redir_list)
{
	if (redir_list == NULL)
		return (NULL);
	while (redir_list->next != NULL)
		redir_list = redir_list->next;
	return (redir_list);
}

void	list_redir_add_back(t_redir **redir_list, t_redir *redir_node)
{
	t_redir	*redir_tmp;

	if (!redir_node)
		return ;
	else if (!(*redir_list))
	{
		*redir_list = redir_node;
		return ;
	}
	redir_tmp = list_redir_last(*redir_list);
	redir_tmp->next = redir_node;
	return ;
}

t_redir	*list_redir_free_node(t_redir *redir_node)
{
	t_redir	*redir_tmp;

	redir_tmp = redir_node->next;
	if (redir_node->file != NULL)
		free(redir_node->file);
	free(redir_node);
	return (redir_tmp);
}

void	list_redir_free_list(t_redir *redir_list)
{
	t_redir	*redir_current;

	if (redir_list == NULL)
		return ;
	redir_current = redir_list;
	while (redir_current != NULL)
		redir_current = list_redir_free_node(redir_current);
	return ;
}
