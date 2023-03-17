#include <minishell.h>

t_token	*parser_id_pipe(t_cmd *cmd_node, t_token *t_current)
{
	(void) cmd_node;
	(void) t_current;
	return (NULL);
}

t_redir_id redir_identification(const char *str)
{
	if (str == NULL)
		return (0);
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (HERE);
		return (IN);
	}
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APP);
		return (OUT);
	}
	return (0);
}

t_token	*parser_id_redir(t_cmd *cmd_node, t_token *t_current)
{
	t_token	*t_file = list_token_skip_space(t_current);
	t_redir	*redir_node;

	redir_node = list_redir_new();
	if (!redir_node)
	{
		cmd_node->next = (t_cmd *) 0XFF;
		return (NULL);
	}
	redir_node->redir = redir_identification(t_current->str);
	redir_node->file = t_current->str;
	list_redir_add_back(&(cmd_node->redir), redir_node);
	return (list_token_skip_space(t_file));
}

t_token	*parser_id_word(t_cmd *cmd_node, t_token *t_current)
{
	size_t	i;
	char	**arr = cmd_node->args;

	i = 0;
	while (arr[i] != NULL)
		i++;
	arr[i] = t_current->str;
	return (list_token_skip_space(t_current));
}

t_token	*parser_id_space(t_cmd *cmd_node, t_token *t_current)
{
	(void) cmd_node;
	return (t_current->next);
}
