#include <minishell.h>

void	lexer_parser(t_minishell *mini)
{
	mini->token = lexer(mini->input);
	printf("\t -=- END LEXER -=-\n\n");
	syntax_check(mini->token);
	printf("\t -=- END SYNTAX -=-\n\n");
	printf("\t -=- END PARSER -=-\n\n");
}
