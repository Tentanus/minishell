#include <minishell.h>

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

t_token	*list_token_last(t_token *list)
{
	int	size;

	size = list_token_size(list);
	while (size-- > 1)
		list = list->next;
	return (list)

void	list_token_add_back(t_token **list t_token *new)
{
	int		size;
	t_token	*tmp;

	if (!new)
		minishell_error(); // Malloc has return NULL in prior call
	else if (!(*list))
	{
		*list = new;
		return ;
	}
	tmp = list_token_last(list);
	tmp->next = new;
}

void	list_token_print(t_token *top)
{
	int			list_size = list_token_size(top);
	const int	con = list_size;

	while (size--)
	{
		ft_printf("TOKEN [%d]\nstr:\t|%s|\ntoken:\t|%d|\n", top->str, top->id, (con -size));
		top = top->next;
	}
	return ;
}


