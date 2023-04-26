#include <minishell.h>

void	complexer(t_minishell *mini)
{
	mini->token = lexer(mini->input);
	// list_token_print(mini->token);
	if (mini->token == NULL)
		minishell_error("tokenization error");
	mini->syntax = syntax(mini->token, mini->env_list);
	if (mini->syntax)
	{
		minishell_syntax_error(mini->syntax->str);
		list_token_free_list(mini->token, list_token_free_node_str);
		return ;
	}
	mini->token = expander(mini->token, mini->env_list);
	// list_token_print(mini->token);
	if (appender(mini) == false)
		return (list_token_free_list(mini->token, list_token_free_node_str));
	mini->cmd_list = parser(mini);
	mini->token = NULL;
	// list_cmd_print(mini->cmd_list);
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
