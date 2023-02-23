#include <minishell.h>

bool	syntax_id_quote(const t_token *n_prev, const t_token *n_cur)
{
	(void) n_prev;
	(void) n_cur;
	return (0);
}

bool	syntax_id_pipe(const t_token *n_prev, const t_token *n_cur)
{
	const t_token	*n_next = skip_space_token((t_token *) n_cur);

	if (n_prev == NULL || n_next == NULL)
		return (1);
	if (ft_strlen(n_cur->str) != 1)
		return (1);
	return (0);
}

bool	syntax_id_redir(const t_token *n_prev, const t_token *n_cur)
{
	const t_token	*n_next = skip_space_token((t_token *) n_cur);

	(void) n_prev;
	if (n_next == NULL)
		return (1);
	if (n_next->id != WORD || ft_strlen(n_cur->str) > 2)
		return (1);
	return (0);
}

bool	syntax_id_word(const t_token *n_prev, const t_token *n_cur)
{
	(void) n_prev;
	(void) n_cur;
	return (0);
}
