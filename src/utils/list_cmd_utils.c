#include <minishell.h>

t_cmd	*list_cmd_new(void)
{
	t_cmd	*cmd_ret;

	cmd_ret = malloc(sizeof(t_cmd) * 1);
	if (!cmd_ret)
		return (NULL);
	cmd_ret->simple_cmd = NULL;
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

void	free_cpp_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i]);
	free(arr);
	return ;
}

t_cmd	*list_cmd_free_node(t_cmd *cmd_node)
{
	t_cmd	*cmd_tmp = cmd_node->next;

	if (cmd_node->simple_cmd != cmd_node->args[0])
		free(cmd_node->simple_cmd);
	cmd_node->simple_cmd = NULL;
	if (cmd_node->args != NULL)
		free_cpp_array(cmd_node->args);
	cmd_node->args = NULL;
	if (cmd_node->redir != NULL)
		list_redir_free_list(cmd_node->redir);
	cmd_node->redir = NULL;
	return (cmd_tmp);
}

void	list_cmd_free_list(t_cmd *cmd_list)
{
	t_cmd	*cmd_current;

	if (cmd_list == NULL)
		return ;
	cmd_current = cmd_list;
	while (cmd_current != NULL)
		cmd_current = list_cmd_free_node(cmd_current);
	return ;
}
