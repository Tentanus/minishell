#include <minishell.h>

t_token_id	token_delimiter(const char c)
	{
	t_token_id	val;
	const char	delim[] = "-\'\"|>< ";

	val = UNINITIALIZED + 1;
	while (val != WORD)
	{
		if (delim[val] == c)
			break ;
		val++;
	}
	return (val);
}

void	get_token_info(const char *inp, int *current_pos, t_token *node)
{
	const int	start_pos = *current_pos;
	node->id = token_delimiter(inp[start_pos]);

	while (inp[*current_pos] && node->id == token_delimiter(inp[*current_pos]))
		(*current_pos)++;
	node->str = ft_substr(inp, start_pos, (*current_pos - start_pos));
}

t_token	*lexer(char *inp)
{
	int				current_pos;
	t_token			*top;
	t_token			*node;

	top = NULL;
	current_pos = ft_skip_whitespace(inp);
	while (inp[current_pos])
	{
		node = list_token_new();
		if (!node)
			minishell_error("lexer/lexer.c: lexer @ malloc");
		get_token_info(inp, &current_pos, node);
		list_token_add_back(&top, node);
		current_pos += ft_skip_whitespace(&inp[current_pos]);
	}
	return (top);
}












/*
1. if end of input is recognised current token shall be delimited.
	if there is no current token END_INP shall be returned.
	
	example:
	c ='\0'
	=>  token delimited

2. if the previous char was an operator and current char (unqouted) can be used
	with the previous chars it shall be used as part of that operator.
	
	example:
	c_prev = '>'
	c = '>'
	=>  token = '>>'

3. if the previous char was used as part of an operator and the current char
	cannot be used with the previous chars to form an operator,
	the operator containing the pervious chars shall be delimited.
	
	example:
	c_prev = ">>"
	c = 'a'
	=> token delimited (+ new token started?)

4. if the current char is backslash '\', single-quote ''', double-quote '"' and
	it is unquited, it shall affect quoting for subsequent characters
	upto the end of the quoted
	
	example:
	echo ""'$PATH'""
	=> doesn't expland PATH since both double quotes close and single quotes
	won't expand

	echo "'$PATH'"
	=> expands PATH with single quote at both sides

	echo '"'$PATH'"'
	=> expands PATH with double quotes at both sides

5. if the currrent character is an unquoted '$', the shell will identify
	the start of any candidates for parameter-expansion.
	
	not quite sure what an example is of this.
	example:
	echo $P"AT"H
	ATH
	=> expands $P [EMPTY] then prints the rest of the input being "AT" and H

6. if the current char is not quoted and can be used as the first char
	of a new operator, the current token shall be delimeted.
	the current char shall be used as the beginning of the next (operator)
	token.

7. if the current char is an unquoted <newline> '\n', the current token shall
	be delimited.

8. if the current char is an unquoted <blank>, any token containing 
	the previous char is delimited and the current char shall be discarded.

9. if the previous char was part of a word, the current char shall be appended
	to the word.

10. if the current char is a '#', it and all subsequent chars up to, but 
	excluding, the next <newline> '\n' shall be discarded as a comment.
	the <newline> '\n' shall not be considered part of the comment.

11. ifthe current char is used as the start of a new word.
*/
