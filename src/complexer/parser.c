/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 14:40:56 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/16 14:30:22 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

typedef t_token*	(*t_parser_func)(t_cmd *cmd_node, t_token *t_current);

size_t	parser_get_arg(t_token *t_current)
{
	size_t	arg_ret;

	arg_ret = 0;
	if (t_current == NULL)
		return (0);
	while (t_current != NULL && t_current->id != PIPE)
	{
		if (t_current->id == WORD)
			arg_ret++;
		if (t_current->id == GREAT || t_current->id == LESS)
			t_current = list_token_skip_space(t_current);
		t_current = list_token_skip_space(t_current);
	}
	return (arg_ret);
}

bool	parser_fill_cmd_node(t_cmd *cmd_node, t_token *t_current)
{
	const size_t		n_arg = parser_get_arg(t_current);
	const t_parser_func	func[9] = {
	[0] = NULL,
	[1] = parser_id_pipe,
	[2] = parser_id_word,
	[3] = parser_id_word,
	[4] = parser_id_redir,
	[5] = parser_id_redir,
	[6] = NULL,
	[7] = parser_id_space,
	[8] = parser_id_word
	};

	cmd_node->args = ft_calloc(sizeof(char *), (n_arg + 1));
	if (!cmd_node->args)
		return (false);
	while (t_current != NULL)
	{
		t_current = func[t_current->id](cmd_node, t_current);
		if (cmd_node->next != NULL)
			return (list_cmd_free_node(cmd_node), false);
	}
	return (true);
}

t_token	*list_token_skip_pipe(t_token *t_current)
{
	t_token	*t_previous;

	if (t_current == NULL)
		return (NULL);
	while (t_current != NULL)
	{
		t_previous = t_current;
		t_current = t_current->next;
		if (t_previous->id == PIPE)
			break ;
	}
	return (t_current);
}

t_cmd	*parser(t_minishell *mini)
{
	t_token	*t_current;
	t_cmd	*cmd_node;
	t_cmd	*cmd_return;

	t_current = mini->token;
	cmd_return = NULL;
	while (t_current != NULL)
	{
		cmd_node = list_cmd_new();
		if (!cmd_node)
			return (list_token_free_list(mini->token, \
					list_token_free_node_str), \
					NULL);
		if (parser_fill_cmd_node(cmd_node, t_current) == false)
			return (list_token_free_list(mini->token, \
					list_token_free_node_str), \
					list_cmd_free_list(cmd_return), \
					NULL);
		list_cmd_add_back(&cmd_return, cmd_node);
		t_current = list_token_skip_pipe(t_current);
	}
	list_token_free_list(mini->token, list_token_free_node_non_word);
	return (cmd_return);
}
