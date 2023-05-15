/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complexer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 14:35:14 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/15 19:20:56 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	complexer(t_minishell *mini)
{
	mini->token = lexer(mini->input);
	if (mini->token == NULL)
		mini_error(error_print, 1, "tokenization error");
	mini->syntax = syntax(mini->token, mini->env_list);
	if (mini->syntax)
	{
		mini_error(syntax_error, 258, mini->syntax->str);
		list_token_free_list(mini->token, list_token_free_node_str);
		return ;
	}
	mini->token = expander(mini->token, mini->env_list);
	if (appender(mini) == false)
		return (list_token_free_list(mini->token, list_token_free_node_str), \
				mini_error(error_print, 1, "expander: unable to expand"));
	mini->cmd_list = parser(mini);
	if (mini->cmd_list == NULL)
		mini_error(error_print, 1, "parser: unable to parse");
	mini->token = NULL;
}

/* IF mini->syntax contains a token the syntax has encountered a error at this
 * token.
 * returning at this point still need to be implemented
bash-3.2$ ./a.out echo "$VAR" $VAR a"$VAR""b"

arg[0]:	|./a.out|
arg[1]:	|echo|
arg[2]:	||
arg[3]:	|ab|

	list_token_print(mini->token);
*/
