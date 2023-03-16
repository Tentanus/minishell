#include <minishell.h>

bool	non_app_token(t_token *t_node)
{
	if (t_node == NULL)
		return (true);
	if (t_node->id == TOKEN || \
		t_node->id == PIPE || \
		t_node->id == GREAT || \
		t_node->id == LESS || \
		t_node->id == SH_VAR || \
		t_node->id == SPACEBAR)
		return (true);
	return (false);
}

bool	append_tokens(t_token *t_previous, t_token *t_current)
{
	t_previous->str = ft_strjoin_fs1(t_previous->str, t_current->str);
	if (!t_previous->str)
		return (false);
	t_previous->next = list_token_free_node(t_current);
	t_previous->id = WORD;
	return (true);
}

bool	appender(t_token *t_list)
{
	t_token	*t_current;
	t_token	*t_previous;

	t_current = t_list;
	t_previous = NULL;
	while (t_current != NULL)
	{
		if (non_app_token(t_previous) || non_app_token(t_current))
		{
			t_previous = t_current;
			t_current = t_current->next;
			continue ;
		}
		if (append_tokens(t_previous, t_current) == false)
			return (list_token_free_list(t_list, list_token_free_node_str), \
					false);
		t_current = t_previous->next;
	}
	return (true);
}
