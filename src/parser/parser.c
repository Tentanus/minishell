#include <minishell.h>

void	lexer_parser(t_minishell *mini)
{
	mini->token = lexer(mini->input);
	if (mini->token == NULL)
		minishell_error("tokenization error");
	printf("\t -=- END LEXER -=-\n");
	list_token_print(mini->token);
	mini->syntax = syntax(mini->token);
	if (mini->syntax)
	{
		minishell_syntax_error(mini->token, mini->syntax->str);
		return ;
	}
	printf("\t -=- END SYNTAX -=-\n");
//	mini->token = expander(mini->token);
	printf("\t -=- END EXPANDER -=-\n");
//	parser(mini->token
	printf("\t -=- END PARSER -=-\n");
//	list_token_free(mini->token);
}

/* IF mini->syntax contains a token the syntax has encountered a error at this
 * token.
 * returning at this point still need to be implemented
 */
