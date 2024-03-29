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
	const char	c = inp[*pos];
	int			i;

	(void) val;
	i = 0;
	while (i < 3 && inp[*pos] && inp[*pos] == c)
	{
		(*pos)++;
		i++;
	}
}

/*
** token_id_shvar
** first character of "name" should be alphabetic (isalpha) or underscore "_"
** rest of characters of "name" should be alphabetic
** or numeric (isalnum) or "_" underscore
*/
void	token_id_shvar(const char *inp, size_t *pos, const t_token_id val)
{
	(void) val;
	(*pos)++;
	// TODO: update validation according to rules in note above ^
	if (inp[*pos] == '?')
	{
		(*pos)++;
		return ;
	}
	if (inp[*pos] && !ft_isalpha(inp[*pos]))
		return ;
	(*pos)++;
	while (inp[*pos] && (ft_isalnum(inp[*pos]) || inp[*pos] == '_'))
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
