/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_cmd_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:41:12 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/08 13:41:13 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*list_cmd_new(void)
{
	t_cmd	*cmd_ret;

	cmd_ret = malloc(sizeof(t_cmd) * 1);
	if (!cmd_ret)
		return (NULL);
	cmd_ret->args = NULL;
	cmd_ret->redir = NULL;
	cmd_ret->next = NULL;
	return (cmd_ret);
}

t_cmd	*list_cmd_last(t_cmd *cmd_list)
{
	if (cmd_list == NULL)
		return (NULL);
	while (cmd_list->next != NULL)
		cmd_list = cmd_list->next;
	return (cmd_list);
}

void	list_cmd_add_back(t_cmd **cmd_list, t_cmd *cmd_node)
{
	t_cmd	*cmd_tmp;

	if (!cmd_node)
		return ;
	else if (!(*cmd_list))
	{
		*cmd_list = cmd_node;
		return ;
	}
	cmd_tmp = list_cmd_last(*cmd_list);
	cmd_tmp->next = cmd_node;
	return ;
}

t_cmd	*list_cmd_free_node(t_cmd *cmd_node)
{
	t_cmd	*cmd_tmp;

	cmd_tmp = cmd_node->next;
	if (cmd_node->args != NULL)
		ft_free_split(cmd_node->args);
	cmd_node->args = NULL;
	if (cmd_node->redir != NULL)
		list_redir_free_list(cmd_node->redir);
	cmd_node->redir = NULL;
	free(cmd_node);
	return (cmd_tmp);
}

void	list_cmd_free_list(t_cmd *cmd_list)
{
	if (cmd_list == NULL)
		return ;
	while (cmd_list != NULL)
		cmd_list = list_cmd_free_node(cmd_list);
	return ;
}
