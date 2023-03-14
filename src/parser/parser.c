#include <minishell.h>

typedef t_token*	(*t_parser_func)(t_cmd *cmd_node, t_token *t_current);

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

size_t	parser_get_arg(t_token *t_current)
{
	size_t	arg_ret;

	arg_ret = 0;
	if (t_current == NULL)
		return (0);
	while (t_current != NULL || t_current->id != PIPE)
	{
		if (t_current->id == QUOTE || t_current->id == DQUOTE || \
			t_current->id == WORD)
			arg_ret++;
		if (t_current->id == GREAT || t_current->id == LESS)
			t_current = t_current->next;
		else if (t_current->next->id == SPACEBAR)
			t_current = t_current->next;
		t_current = t_current->next;
	}
	return (arg_ret);
}

t_token	*parser_fill_cmd_node(t_cmd *cmd_node, t_token *t_current)
{
	const t_parser_func	func[9] = {
		[0] = NULL,
		[1] = parser_id_pipe,
		[2] = parser_id_,
		[3] = parser_id_,
		[4] = parser_id_,
		[5] = parser_id_,
		[6] = parser_id_,
		[7] = parser_id_,
		[8] = parser_id_,
	};

	cmd_node->args = malloc(sizeof(char *) * (parser_get_arg(t_current) + 1));
	if (!cmd_node->args)
		return (false);
	cmd_node->args[n_args] = NULL;
	while (t_current != NULL)
	{
		t_current = func[t_current->id](cmd_node, t_current);
		if (cmd_node->next != NULL)
			return (list_cmd_free_node(cmd_node), false);
	}
	return (true);
}

t_token	*parser_pipe_next(t_token *t_current)
{
	if (t_current == NULL)
		return (NULL);
	while (t_current != NULL || t_current->id != PIPE)
		t_current = t_current->next;
	if (t_current == NULL)
		return (NULL);
	return (t_current->next);
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
			return (list_token_free_list(t_list, list_token_free_node_str), \
					NULL);
		if (parser_fill_cmd_node(cmd_node, t_current) == false) //subfunction should free cmd_node
			return (list_token_free_list(t_list, list_token_free_node_str), \
					list_cmd_free_list(cmd_return), \
					NULL);
		list_cmd_add_back(&cmd_return, cmd_node);
		t_current = parser_pipe_next(t_current);
	}
	list_token_free_list(t_list, list_token_free_node);
	return (cmd_return);
}

// add extra function: that skips the free for WORD_QUOTE_DQUOTE 
//free_node_PIPE_GREAT_LESS_SPACEBAR
//
//test case in bash:
//
// >$ <infile
// >$ echo $?
// .$ 0
//
