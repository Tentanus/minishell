#include <minishell.h>

void	token_id_quote(const char *inp, size_t *pos, const t_token_id val)
{
	(*pos)++;
	while (inp[*pos] && val != get_char_id(inp[*pos]))
		(*pos)++;
	if (inp[*pos])
		(*pos)++;
}

void	token_id_pipe(const char *inp, size_t *pos, const t_token_id val)
{
	int	i;

	(void) val;
	i = 0;
	while (i < 2 && inp[*pos] && inp[*pos] == '|')
	{
		(*pos)++;
		i++;
	}
}

void	token_id_redir(const char *inp, size_t *pos, const t_token_id val)
{
	int	i;

	(void) val;
	i = 0;
	while (i < 3 && inp[*pos] && (inp[*pos] == '>' || inp[*pos] == '<'))
	{
		(*pos)++;
		i++;
	}
}

void	token_id_shvar(const char *inp, size_t *pos, const t_token_id val)
{
	(void) val;
	(*pos)++;
	if (inp[*pos] == '?' || inp[*pos] == '$')
	{
		(*pos)++;
		return ;
	}
	while (inp[*pos] && ft_isalnum(inp[*pos]))
		(*pos)++;
}

/*
 * if $$$
 * tokenizer will give
 *   [0]	$$
 *   [1]	$
 */

void	token_id_misc(const char *inp, size_t *pos, const t_token_id val)
{
	while (inp[*pos] && val == get_char_id(inp[*pos]))
		(*pos)++;
}