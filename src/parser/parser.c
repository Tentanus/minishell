#include <minishell.h>

t_token	*parser_get_next_block(t_token *t_current)
{
	t_token	*t_previous;

	if (t_current == NULL)
		return (NULL);
	while (t_current != NULL || t_previous->id != PIPE)
	{
		t_previous = t_current;
		t_current = t_current->next;
	}
	return (t_current);
}

parser_fill_cmd_node(t_cmd *cmd_node, t_token *t_current)
{
	unsigned int	n_args;

	ui_args = 
	while (t_current != NULL || t_current != PIPE)
	{
		t_current = func[t_current->id]
	}
}

t_cmd	*parser(t_token *t_list)
{
	t_token	*t_current;
	t_cmd	*cmd_node;
	t_cmd	*cmd_return;

	t_current = t_list;
	cmd_return = NULL;
	while (t_current != NULL)
	{
		cmd_node = list_cmd_new();
		if (!cmd_node)
			return (list_token_free_list(t_list, list_token_free_node_str));
		parser_fill_cmd_node(cmd_node, t_current);
		list_cmd_add_back(&cmd_return, cmd_node);
		t_current = parser_get_next_block(t_current); 
	}
	list_token_free_list(mini->token, list_token_free_node);
}
// add extra function: that skips the free for WORD_QUOTE_DQUOTE 
//free_node_PIPE_GREAT_LESS_SPACEBAR
