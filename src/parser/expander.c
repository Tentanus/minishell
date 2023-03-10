#include <minishell.h>

t_token	*expander_shell_var_spacer(char *str)
{
	t_token	*t_return;
	t_token	*t_node;

	t_node = list_token_new();
	if (!t_node)
		return (NULL);
	t_node->id = WORD;
	t_node->str = str;
	list_token_add_back(&t_return, t_node);
	t_node = list_token_new();
	if (!t_node)
		return (list_token_free_list(t_return), NULL);
	t_node->id = SPACE;
	t_node->str = NULL;
	list_token_add_back(&t_return, t_node);
	return (t_return);
}

t_token	*expander_shell_var(t_token *t_current, t_env_var_ll *env_var_list)
{
	t_token	*t_return;
	t_token	*t_node;
	char	**cpp_split;
	char	*var;
	size_t	i;

	t_return = NULL;
	i = 0;
	var = t_current->str + 1;
	cpp_split = ft_split(env_var_get_env(var, env_var_list), ' ');
	if (!cpp_split)
		return (NULL);
	while (cpp_split[i] != NULL)
	{
		t_node = expander_shell_var_spacer(cpp_split[i]);
		if (!t_node)
			return (list_token_free_list(t_return), NULL);
		list_token_add_back(&t_return, t_node);
		i++;
	}
	free(cpp_split);
	return (t_return);
}

void	expander_remove_quotes(t_token *t_node)
{
	char			*str;
	const size_t	len = ft_strlen(t_node->str);

	if (len < 2)
		return ;
	str = t_node->str;
	ft_memmove(str, str + 1, len);
	ft_memmove(&str[len - 2], &str[len - 1], 1);
	return ;
}

int	expander_inject_var(t_token *t_current, const int pos, \
		t_env_var_ll *env_var_list)
{
	size_t	len_sh_expand;
	size_t	len_sh_var;
	char	*sh_expand;
	char	*sh_var;
	char	*new_token_str;

	len_sh_var = 0;
	token_id_shvar((t_current->str) + pos, &len_sh_var, 0);
	sh_var = ft_substr(t_current->str, pos + 1, len_sh_var - 1);
	if (!sh_var)
		return (-1);
	sh_expand = env_var_get_env(sh_var, env_var_list);
	len_sh_expand = ft_strlen(sh_expand);
	new_token_str = malloc(sizeof(char) * (ft_strlen(t_current->str) - \
				len_sh_var + len_sh_expand + 1));
	if (!new_token_str)
		return (-1);
	ft_strlcpy(new_token_str, t_current->str, pos);
	ft_strlcat(new_token_str, sh_expand, len_sh_expand);
	ft_strlcat(new_token_str, &(t_current->str)[pos + len_sh_expand], pos);
	free(sh_var);
	free(t_current->str);
	t_current->str = new_token_str;
	return (len_sh_expand);
}

/*
 * make int i a size_t to give the starting position of the shellvariable
 *
 * also look over all the functions in this file to see if it makes sense
 */

t_token	*expander_quote(t_token *t_current, t_env_var_ll *env_var_list)
{
	int		i;
	int		tmp;

	expander_remove_quotes(t_current);
	if (t_current->str == NULL)
		return (NULL);
	if (t_current->id == QUOTE)
		return (list_token_cpy_node(t_current));
	i = 0;
	while (t_current->str[i])
	{
		printf("|%s|\n", t_current->str);
		if (t_current->str[i] == '$')
		{
			tmp = expander_inject_var(t_current, i, env_var_list);
			if (tmp < 0)
				return (NULL);
			i += tmp;
		}
		else
			i++;
	}
	return (list_token_cpy_node(t_current));
}

t_token	*expander(t_token *t_input, t_env_var_ll *env_var_list)
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
			t_node = expander_shell_var(t_current, env_var_list);
		else if (t_current->id == DQUOTE || t_current->id == QUOTE)
			t_node = expander_quote(t_current, env_var_list);
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
