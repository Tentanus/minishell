#include <minishell.h>

void	lexer_parser(t_minishell *mini)
{
	mini->token = lexer(mini->input);
	printf("\t -=- END LEXER -=-\n\n");
	list_token_print(mini->token);
	syntax_check(mini->token);
	printf("\t -=- END SYNTAX -=-\n\n");
	mini->token = expander(mini->token);
	printf("\t -=- END EXPANDER -=-\n\n");
//	parser(mini->token
	printf("\t -=- END PARSER -=-\n\n");
//	list_token_free(mini->token);
}
