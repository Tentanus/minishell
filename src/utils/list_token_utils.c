#include <minishell.h>

size_t	list_token_size(t_token *t_list)
{
	size_t	size;

	size = 0;
	while (t_list != NULL)
	{
		t_list = t_list->next;
		size++;
	}
	return (size);
}

t_token	*list_token_new(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token) * 1);
	if (!new)
		minishell_error("utils/list_token_utils.c: list_token_new @ malloc");
	new->next = NULL;
	new->id = UNINITIALIZED;
	new->str = NULL;
	return (new);
}

t_token	*list_token_last(t_token *list)
{
	size_t	size;

	size = list_token_size(list);
	while (size-- > 1)
		list = list->next;
	return (list);
}

t_token	*list_token_cpy_node(t_token *t_node)
{
	t_token	*t_return;

	if (!t_node)
		return (NULL);
	t_return = list_token_new();
	t_return->id = t_node->id;
	t_return->str = ft_strdup(t_node->str);
	if (t_return->str == NULL)
		return (free(t_return), NULL);
	return (t_return);
}

void	list_token_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	else if (!(*list))
	{
		*list = new;
		return ;
	}
	tmp = list_token_last(*list);
	tmp->next = new;
	return ;
}

void	list_token_free(t_token *t_list)
{
	t_token *t_current;
	t_token *t_tmp;

	t_current = t_list;
	while (t_current != NULL)
	{
		free(t_current->str);
		t_tmp = t_current;
		t_current = t_current->next;
		free(t_tmp);
	}
}
