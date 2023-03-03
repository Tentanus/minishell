#include <minishell.h>

void	expander_token(t_token *t_previous, t_token *t_next, \
		t_token *t_list)
{
	char	*str_previous;
	char	*str_next;

	(void) t_next;
	if (t_previous->id == WORD)
	{
		str_previous = t_previous->str;
		str_next = *t_list->str;
		
		*t_list = list_token_free_node(*t_list);
		
	}
}

t_token	*expander_shell_var(t_token *t_previous, t_token *t_current)
{
	t_token	*t_return;
	t_token	*t_node;
	char	**cpp_split;
	size_t	i;

	t_return = NULL;
	i = 0;
	cpp_split = ft_split(get_env(t_current->str + 1), ' ');
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
	expander_append_tokens(t_previous, t_current->next, &t_return);
	return (t_return);
}

/*
	if (t_previous->id == WORD)
//		t_return = t_return->next;
//		t_tmp = t_return;
//		t_tmp->next = NULL;
		list_token_append&remove(t_previous, t_return);
	if (t_current->next->id == DQUOTE)
		list_token_add_quotes
*/

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
		else if (t_current->id == DQUOTE)
			t_node = expander_quote(t_previous, t_current);
		else
			t_node = list_token_cpy_node(t_current);
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
