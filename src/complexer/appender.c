#include <minishell.h>

bool	app_token(t_token *t_node)
{
	if (t_node == NULL)
		return (false);
	if (t_node->id == WORD || \
		t_node->id == DQUOTE || \
		t_node->id == QUOTE)
		return (true);
	return (false);
}

bool	appender(t_token *t_list)
{
	t_token	*t_current;
	t_token	*t_previous;

	t_current = t_list;
	t_previous = NULL;
	while (t_current != NULL)
	{
		if (app_token(t_previous) && app_token(t_current))
		{
			t_previous->str = ft_strjoin_fs1(t_previous->str, t_current->str);
			if (t_previous->str == NULL)
				return (false);
			t_current = list_token_free_node_str(t_current);
			t_previous->next = t_current;
			continue ;
		}
		t_previous = t_current;
		t_current = t_current->next;
	}
	return (true);
}