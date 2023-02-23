#include <minishell.h>

void	lexer_parser(t_minishell *mini)
{
	mini->token = lexer(mini->input);
	printf("\t -=- END LEXER -=-\n\n");
	list_token_print(mini->token);
//	syntax_check(mini->token);		still need to add the SHELL_VAR function to jumptable
	printf("\t -=- END SYNTAX -=-\n\n");
//	expander(mini->token);			lexer has SHELL_VAR as separate tokens
	printf("\t -=- END PARSER -=-\n\n");
}
