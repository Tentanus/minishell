#include <minishell.h>

void	token_id_quote(const char *inp, size_t *pos, const t_token_id val)
{
	(*pos)++;
	while (inp[*pos] && val != get_char_id(inp[*pos]))
		(*pos)++;
	(*pos)++;
}

void	token_id_misc(const char *inp, size_t *pos, const t_token_id val)
{
	while (inp[*pos] && val == get_char_id(inp[*pos]))
		(*pos)++;
}

