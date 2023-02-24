#include <minishell.h>

bool	syntax_id_pipe(const t_token *t_prev, const t_token *t_cur)
{
	const t_token	*t_next = skip_space_token((t_token *) t_cur);

	if (t_prev == NULL || t_next == NULL)
		return (1);
	if (ft_strlen(t_cur->str) != 1)
		return (1);
	return (0);
}

bool	syntax_id_redir(const t_token *t_prev, const t_token *t_cur)
{
	const t_token	*t_next = skip_space_token((t_token *) t_cur);

	(void) t_prev;
	if (t_next == NULL)
		return (1);
	if (t_next->id != WORD || ft_strlen(t_cur->str) > 2)
		return (1);
	return (0);
}

bool	syntax_id_misc(const t_token *t_prev, const t_token *t_cur)
{
	(void) t_prev;
	(void) t_cur;
	return (0);
}
