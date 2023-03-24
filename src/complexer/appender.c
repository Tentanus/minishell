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

t_token	*app_remove_empty_token(t_token *t_list)
{
	t_token	*t_current;
	t_token	*t_previous;

	if (t_list == NULL)
		return (NULL);
	t_current = t_list;
	t_previous = NULL;
	while (t_current != NULL)
	{
		if (t_current->str != NULL)
		{
			t_previous = t_current;
			t_current = t_current->next;
			continue ;
		}
		t_current = list_token_free_node(t_current);
		if (t_previous == NULL)
			t_list = t_current;
		else
			t_previous->next = t_current;
	}
	return (t_list);
}

bool	appender(t_minishell *mini)
{
	t_token	*t_current;
	t_token	*t_previous;

	mini->token = app_remove_empty_token(mini->token);
	t_current = mini->token;
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
