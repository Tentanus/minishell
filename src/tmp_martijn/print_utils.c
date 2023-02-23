#include <minishell.h>

// TESTING FUNCTION

void	list_token_print(t_token *top)
{
	int			size = list_token_size(top);
	const int	con = size;
	const char	*token_name[8] = {
		[0] = "PIPE",
		[1] = "QUOTE",
		[2] = "DOUBLE QUOTE",
		[3] = "GREAT",
		[4] = "LESS",
		[5] = "SHELL_VAR",
		[6] = "SPACE",
		[7] = "WORD"
	} ;

	printf("\n\t-=-  TOKEN PRINT -=-\n");
	while (size--)
	{
		ft_printf("TOKEN [%d]\n\tstr:\t|%s|\n\ttoken:\t%s [%d]\n", (con - size), top->str,  token_name[top->id], top->id);
		top = top->next;
	}
	return ;
}

