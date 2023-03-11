#include <minishell.h>

void	parser(t_minishell *mini)
{
	list_token_free_list(mini->token, list_token_free_node);
}
