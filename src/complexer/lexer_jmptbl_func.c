/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_jmptbl_func.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 14:39:50 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/12 15:27:59 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

void	token_id_shvar(const char *inp, size_t *pos, const t_token_id val)
{
	(void) val;
	(*pos)++;
	if (inp[*pos] == '?')
	{
		(*pos)++;
		return ;
	}
	if (!ft_isalpha(inp[*pos]))
		return ;
	if (inp[*pos])
		(*pos)++;
	while (inp[*pos] && (ft_isalnum(inp[*pos]) || inp[*pos] == '_'))
		(*pos)++;
}

void	token_id_misc(const char *inp, size_t *pos, const t_token_id val)
{
	while (inp[*pos] && val == get_char_id(inp[*pos]))
		(*pos)++;
}
