#include <minishell.h>

// TESTING FUNCTION

void	list_token_print(t_token *top)
{
	int			size = list_token_size(top);
	const int	con = size;
	const char	*token_name[9] = {
		[0] = "TOKEN",
		[1] = "PIPE",
		[2] = "QUOTE",
		[3] = "DOUBLE QUOTE",
		[4] = "GREAT",
		[5] = "LESS",
		[6] = "SHELL_VAR",
		[7] = "SPACE",
		[8] = "WORD"
	} ;

	printf("\n\t-=-  TOKEN PRINT -=-\n");
	while (size--)
	{
		ft_printf("TOKEN [%d]\tid:  %s [%d]\n\t\tstr: |%s|\n", (con - size),  token_name[top->id], top->id, top->str);
		top = top->next;
	}
	return ;
}

