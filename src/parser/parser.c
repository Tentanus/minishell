#include <minishell.h>

void	syntax_check(t_token *top)
{
	
}

void parser(t_minishell *mini)
{
	mini->token = lexer(mini->inp);
	syntax_check(mini->token);

}
