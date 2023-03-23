#include <minishell.h>

void	complexer(t_minishell *mini)
{
	mini->token = lexer(mini->input);
	if (mini->token == NULL)
		minishell_error("tokenization error");
	//printf("\t-=- END LEXER -=-\n");
	mini->syntax = syntax(mini->token);
	if (mini->syntax)
	{
		minishell_syntax_error(mini->syntax->str);
		list_token_free_list(mini->token, list_token_free_node_str);
		return ;
	}
	// printf("\t-=- END SYNTAX -=-\n");
	mini->token = expander(mini->token, mini->env_list);
	// printf("\t-=- END EXPANDER -=-\n");
	if (appender(mini->token) == false)
		return (list_token_free_list(mini->token, list_token_free_node_str));
	// printf("\t-=- END APPENDER -=-\n");
	mini->cmd_list = parser(mini->token);
	mini->token = NULL;
	// printf("\t-=- END PARSER -=-\n");
	list_cmd_print(mini->cmd_list);
	// list_cmd_free_list(mini->cmd_list); // remove once testing complexer is finished
}

/* IF mini->syntax contains a token the syntax has encountered a error at this
 * token.
 * returning at this point still need to be implemented
 */
