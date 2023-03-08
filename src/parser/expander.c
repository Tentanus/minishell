#include <minishell.h>

t_token	*expander_shell_var(t_token *t_previous, t_token *t_current)
{
	t_token	*t_return;
	t_token	*t_node;
	char	**cpp_split;
	size_t	i;

	t_return = NULL;
	i = 0;
	cpp_split = ft_split(env_var_get_env(t_current->str), ' ');
	if (!cpp_split)
		return (NULL);
	while (cpp_split[i] != NULL)
	{
		t_node = list_token_new();
		if (!t_node)
			return (list_token_free_list(t_return), NULL);
		t_node->id = WORD;
		t_node->str = cpp_split[i];
		list_token_add_back(&t_return, t_node);
		i++;
	}
	free(cpp_split);
	return (t_return);
}

void	expander_remove_quotes(t_token *t_node)
{
	char	*str;

	str = t_node->str;
	if (t_node->id == QUOTE)
		t_node->str = ft_strtrim(t_node->str, "\'");
	else if (t_node->id == DQUOTE)
		t_node->str = ft_strtrim(t_node->str, "\"");
	free(str);
	return ;
}

t_token	*expander_quote(t_token *t_previous, t_token *t_current)
{
	t_token	*t_node;

	expander_remove_quotes(t_current);
	if (t_current->str == NULL)
		return (NULL);
	if (t_current->id == QUOTE)
		return (list_token_cpy_node(t_current));
	
}

t_token	*expander_token_append(t_token *t_previous, t_token **t_list)
{
	t_token	*t_return;

	if (t_previous->id != QUOTE && t_previous->id != DQUOTE && \
			t_previous->id != WORD)
		return (*t_list);
	t_previous->str = ft_strjoin_fs1(t_previous->str, (*t_list)->str);
	if (t_previous->str == NULL)
		return (list_token_free_list(*t_list), NULL);
	t_return = list_token_free_node(*t_list);
	return (t_return);
}

t_token	*expander(t_token *t_input)
{
	t_token	*t_return;
	t_token	*t_current;
	t_token	*t_node;
	t_token	*t_previous;

	t_return = NULL;
	t_current = t_input;
	while (t_current != NULL)
	{
		if (t_current->id == SH_VAR)
			t_node = expander_shell_var(t_previous, t_current);
		else if (t_current->id == DQUOTE || t_current->id == QUOTE)
			t_node = expander_quote(t_previous, t_current);
		else
			t_node = list_token_cpy_node(t_current);
		t_node = expander_token_append(t_previous, &t_node);
		if (!t_node)
			return (list_token_free_list(t_input), \
					list_token_free_list(t_return), NULL);
		list_token_add_back(&t_return, t_node);
		t_previous = list_token_last(t_return);
		t_current = t_current->next;
	}
	list_token_free_list(t_input);
	return (t_return);
}

//	SH_VAR appends to previous word token
//	SH_VAR adds in front of DQUOTE
/*
 *
 * EXPANSION:
 *
 * --==-- CASE [1] --==--
 *  VAR="b c d"
 *  ./print_arg a$VAR'ef'
 *
 *  1  ab
 *  2  c
 *  3  def
 *
 * --==-- CASE [2] --==--
 *  VAR=""
 *  ./print_arg a$VAR'ef'
 *  
 *  1  aef
 *
 * --==-- CASE [3] --==--
 *  A="b c d"
 *  B="e f g"
 *  ./print_arg a$A$B"h"
 *
 *  1  ab
 *  2  c
 *  3  de
 *  4  f
 *  5  gh
 */
