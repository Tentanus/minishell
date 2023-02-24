#include <minishell.h>

void	lexer_parser(t_minishell *mini)
{
	mini->token = lexer(mini->input);
	printf("\t -=- END LEXER -=-\n\n");
	list_token_print(mini->token);
	syntax_check(mini->token);
	printf("\t -=- END SYNTAX -=-\n\n");
//	expander(mini->token);			lexer has SHELL_VAR as separate tokens
	printf("\t -=- END PARSER -=-\n\n");
	list_token_free(mini->token);
}
