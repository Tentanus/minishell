/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 14:36:13 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/15 19:36:55 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	expander_remove_check_quotes(t_token *t_node)
{
	char			*str;
	const size_t	len = ft_strlen(t_node->str);

	str = t_node->str;
	if (len < 2 || str[0] != str[len - 1])
	{
		mini_error(error_print, 258, "unclosed quotes");
		return (true);
	}
	ft_memmove(str, str + 1, len);
	ft_memmove(&str[len - 2], &str[len - 1], 1);
	return (false);
}

char	*expander_get_shell_var(const char *str, const int pos, \
		size_t *len_sh_var, t_env_var_ll *env_var_list)
{
	char	*str_ret;
	char	*sh_var;

	*len_sh_var = 0;
	token_id_shvar(str + pos, len_sh_var, 0);
	sh_var = ft_substr(str, pos + 1, *len_sh_var - 1);
	if (!sh_var)
		return (NULL);
	str_ret = env_var_get_env(sh_var, env_var_list);
	free(sh_var);
	return (str_ret);
}

int	expander_inject_var(t_token *t_current, const int pos, \
		t_env_var_ll *env_var_list)
{
	size_t	len_sh_expand;
	size_t	len_sh_var;
	char	*sh_expand;
	char	*new_token_str;

	if (!t_current || !t_current->str)
		return (ERROR);
	sh_expand = expander_get_shell_var(t_current->str, pos, &len_sh_var, \
			env_var_list);
	if (!sh_expand)
		len_sh_expand = 0;
	else
		len_sh_expand = ft_strlen(sh_expand);
	new_token_str = ft_calloc(sizeof(char), \
			((ft_strlen(t_current->str) - len_sh_var + len_sh_expand) + 1));
	if (!new_token_str)
		return (ERROR);
	ft_strlcpy(new_token_str, t_current->str, pos + 1);
	ft_strlcat(new_token_str, sh_expand, pos + len_sh_expand + 1);
	ft_strlcat(new_token_str, &(t_current->str)[pos + len_sh_var], \
			(ft_strlen(t_current->str) - len_sh_var + len_sh_expand + 1));
	free(t_current->str);
	t_current->str = new_token_str;
	return (len_sh_expand);
}

t_token	*expander_quote(t_token *t_current, t_env_var_ll *env_var_list)
{
	size_t	i;
	int		tmp;

	if (t_current->str == NULL || expander_remove_check_quotes(t_current))
		return (NULL);
	if (t_current->id == QUOTE)
	{
		t_current->id = WORD;
		return (list_token_cpy_node(t_current));
	}
	i = 0;
	while ((t_current->str)[i])
	{
		if ((t_current->str)[i] == '$' && ft_isalpha((t_current->str)[i + 1]))
		{
			tmp = expander_inject_var(t_current, i, env_var_list);
			if (tmp < 0)
				return (NULL);
			i += (size_t) tmp;
		}
		else
			i++;
	}
	t_current->id = WORD;
	return (list_token_cpy_node(t_current));
}

t_token	*expander(t_token *t_input, t_env_var_ll *env_var_list)
{
	t_token	*t_return;
	t_token	*t_current;
	t_token	*t_node;

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
			return (list_token_free_list(t_input, list_token_free_node_str), \
					list_token_free_list(t_return, list_token_free_node_str), \
					mini_error(error_print, 1, "expander: unable to expand"), \
					NULL);
		list_token_add_back(&t_return, t_node);
		t_current = t_current->next;
	}
	list_token_free_list(t_input, list_token_free_node_str);
	return (t_return);
}
