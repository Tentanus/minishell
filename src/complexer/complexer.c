#include <minishell.h>

void	complexer(t_minishell *mini)
{
	mini->token = lexer(mini->input);
	if (mini->token == NULL)
		minishell_error("tokenization error");
	printf("\t-=- END LEXER -=-\n");
	mini->syntax = syntax(mini->token);
	if (mini->syntax)
	{
		minishell_syntax_error(mini->syntax->str);
		list_token_free_list(mini->token, list_token_free_node_str);
		return ;
	}
	printf("\t-=- END SYNTAX -=-\n");
	mini->token = expander(mini->token, mini->env_list);
	printf("\t-=- END EXPANDER -=-\n");
//	list_token_print(mini->token);
	if (appender(mini) == false)
		return (list_token_free_list(mini->token, list_token_free_node_str));
	printf("\t-=- END APPENDER -=-\n");
	list_token_print(mini->token);
	mini->cmd_list = parser(mini);
	mini->token = NULL;
	printf("\t-=- END PARSER -=-\n");
	list_cmd_print(mini->cmd_list);
	list_cmd_free_list(mini->cmd_list); // remove once testing complexer is finished
}

/* IF mini->syntax contains a token the syntax has encountered a error at this
 * token.
 * returning at this point still need to be implemented
bash-3.2$ ./a.out echo "$VAR" $VAR a"$VAR""b"

arg[0]:	|./a.out|
arg[1]:	|echo|
arg[2]:	||
arg[3]:	|ab|

*/
