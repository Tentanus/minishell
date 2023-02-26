#include <minishell.h>

t_token	*expand_current_token(t_token *t_previous, t_token t_current)
{
	
}

t_token	*expander(t_token *t_input)
{
	t_token	*t_return;
	t_token	*t_node;
	t_token	*t_current;
	t_token	*t_previous;

	t_current = t_input;
	t_previous = NULL;
	t_return = NULL;
	while (t_current != NULL)
	{
		if (t_current->id == SH_VAR || t_current->id == DQUOTE)
			t_node = expand_current_token(t_previous, t_current);
		else
			t_node = list_token_cpy_node(t_current);
		if (!t_node)
			return (list_token_free(t_input), list_token_free(t_return), NULL);
		list_token_add_back(&t_return, t_node);
		t_previous = list_token_last(t_return);
		t_current = t_current->next;
	}
	list_token_free(t_input);
	return (t_return);
}
