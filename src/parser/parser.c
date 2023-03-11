#include <minishell.h>

void	parser(t_minishell *mini)
{
	t_token *t_current;

	t_current = mini->token;
	while (t_current != NULL)
	{
		
	}
	list_token_free_list(mini->token, list_token_free_node);
}
