#include <minishell.h>

typedef bool	(*t_syntax_func) \
			(const t_token *n_prev, const t_token *n_cur);

t_token	*get_next_token(t_token *n_cur)
{
	t_token	*ret;

	ret = n_cur->next;
	if (ret->id == SPACEBAR)
		ret = ret->next;
	return (ret);
}

void	syntax_check(t_token *top)
{
	t_token				*n_prev;
	t_token				*n_cur;
	const t_syntax_func	func[] = {
	[0] = &syntax_id_quote,
	[1] = &syntax_id_quote,
	[2] = &syntax_id_pipe,
	[3] = &syntax_id_redir,
	[4] = &syntax_id_redir,
	[5] = &syntax_id_space,
	[6] = &syntax_id_word
	};

	n_prev = NULL;
	n_cur = top;
	while (n_cur != NULL)
	{
//		list_token_print(n_cur);
		printf("cur:\t%p\nprev:\t%p\n", n_cur, n_prev);
		if (func[n_cur->id] (n_prev, n_cur)) // segfaults with any input
			minishell_syntax_error(*n_cur);
		n_prev = n_cur;
		n_cur = get_next_token(n_cur);
	}
}

void	lexer_parser(t_minishell *mini)
{
	mini->token = lexer(mini->input);
	syntax_check(mini->token);
	printf("\t -=- END PARSER -=-\n");
}
