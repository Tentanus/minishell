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
		return (NULL);
	new->next = NULL;
	new->id = UNINITIALIZED;
	new->str = NULL;
	return (new);
}

t_token	*list_token_last(t_token *t_list)
{
	if (t_list == NULL)
		return (NULL);
	while (t_list->next != NULL)
		t_list = t_list->next;
	return (t_list);
}

t_token	*list_token_cpy_node(t_token *t_node)
{
	t_token	*t_return;

	if (!t_node)
		return (NULL);
	t_return = list_token_new();
	if (!t_return)
		return (NULL);
	t_return->id = t_node->id;
	t_return->str = ft_strdup(t_node->str);
	if (t_return->str == NULL)
		return (free(t_return), NULL);
	return (t_return);
}

void	list_token_add_back(t_token **t_list, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	else if (!(*t_list))
	{
		*t_list = new;
		return ;
	}
	tmp = list_token_last(*t_list);
	tmp->next = new;
	return ;
}

t_token	*list_token_free_node(t_token *t_node)
{
	t_token *t_tmp;

	if (t_node == NULL)
		return (NULL);
	t_tmp = t_node->next;
	if (t_node->str != NULL)
		free(t_node->str);
	free(t_node);
	return (t_tmp);
}

void	list_token_free_list(t_token *t_list)
{
	t_token *t_current;

	if (t_list == NULL)
		return ;
	t_current = t_list;
	while (t_current != NULL)
		t_current = list_token_free_node(t_current);
	return ;
}
