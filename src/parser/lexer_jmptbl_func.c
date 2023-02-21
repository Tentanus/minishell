#include <minishell.h>

void	token_id_quote(const char *inp, size_t *pos, const t_token_id val)
{
	(*pos)++;
	while (inp[*pos] && val != get_char_id(inp[*pos]))
		(*pos)++;
	(*pos)++;
}

void	token_id_pipe(const char *inp, size_t *pos, const t_token_id val)
{
	int i;

	(void) val;
	i = 0;
	while (i < 2 && inp[*pos] && inp[*pos] == '|')
	{
		(*pos)++;
		i++;
	}
}

void	token_id_great(const char *inp, size_t *pos, const t_token_id val)
{
	int i;

	(void) val;
	i = 0;
	while (i < 3 && inp[*pos] && inp[*pos] == '>')
	{
		(*pos)++;
		i++;
	}
}

void	token_id_less(const char *inp, size_t *pos, const t_token_id val)
{
	int i;

	(void) val;
	i = 0;
	while (i < 3 && inp[*pos] && inp[*pos] == '<')
	{
		(*pos)++;
		i++;
	}
}

void	token_id_misc(const char *inp, size_t *pos, const t_token_id val)
{
	while (inp[*pos] && val == get_char_id(inp[*pos]))
		(*pos)++;
}
