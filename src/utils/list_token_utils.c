#include <minishell.h>

/*
	list_token_stize(t_token *top)
*/

int	list_token_size(t_token *top)
{
	int	size;

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
		return (NULL);
	new->next = NULL;
	return (new);
}

t_token	*list_token_last(t_token *list)
{
	int	size;

	size = list_token_size(list);
	while (size-- > 1)
		list = list->next;
	return (list);
}

void	list_token_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;// maybe we should do the minishell exit here to.
	else if (!(*list))
	{
		*list = new;
		return ;
	}
	tmp = list_token_last(*list);
	tmp->next = new;
}

void	list_token_print(t_token *top)
{
	int			size = list_token_size(top);
	const int	con = size;

	while (size--)
	{
		ft_printf("TOKEN [%d]\nstr:\t|%s|\ntoken:\t|%d|\n", top->str, top->id, (con - size));
		top = top->next;
	}
	return ;
}


