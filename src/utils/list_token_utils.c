#include <minishell.h>

size_t	list_token_size(t_token *top)
{
	size_t	size;

	size = 0;
	while (top != NULL)
	{
		top = top->next;
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

void	list_token_free(t_token *top)
{
	t_token *t_current;
	t_token *t_tmp;

	t_current = top;
	while (t_current != NULL)
	{
		free(t_current->str);
		t_tmp = t_current;
		t_current = t_current->next;
		free(t_tmp);
	}
}
