#include <minishell.h>
/*
static const char	*g_id_chars[] = { \
	[BACK_SLASH] = "\\",\
	[DOUB_QUOTE] = "\"",	\
	[PIPE] = "|",		\
	[GREAT] = ">",		\
	[LESS] = "<",		\
	[CHAR_END] = ""
};
*/
int	skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

t_token	*lexer(const char *inp)
{
	int		i;
	t_token	*list_token;

	i = 0;
	list_token = NULL;
	while (inp[i])
	{
		i += skip_whitespace(&inp[i]);

//		list_token_add_back(list_token_new(&inp[i]));
	}
	return (list_token);
}
