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


