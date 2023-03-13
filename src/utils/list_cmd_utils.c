#include <minishell.h>

t_cmd	*list_cmd_new(void)
{
	t_cmd	*cmd_ret;

	cmd_ret = malloc(sizeof(t_cmd) * 1);
	if (!cmd_ret)
		return (NULL);
	cmd_ret->simple_cmd = NULL;
	cmd_ret->args = NULL;
	cmd_ret->amount_of_args = 0;
	cmd_ret->redir = NULL;
	cmd_ret->next = NULL;
}

void	list_cmd_add_back(t_cmd **cmd_list, t_cmd cmd_node)
{
	t_cmd	*cmd_tmp;

	if (!new)
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
