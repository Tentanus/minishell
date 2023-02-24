#include <minishell.h>

typedef void	(*t_delimiter_func) \
			(const char *inp, size_t *pos, const t_token_id val);

t_token_id	get_char_id(const char c)
{
	t_token_id	val;
	const char	set_delimiters[] = "\'\"|>< ";

	val = QUOTE;
	while (val != WORD)
	{
		if (set_delimiters[val] == c)
			break ;
		val++;
	}
	return (val);
}

void	get_token_info(const char *inp, size_t *pos, t_token *node)
{
	const int				start_pos = *pos;
	const t_delimiter_func	func[] = {
	[0] = &token_id_quote,
	[1] = &token_id_quote,
	[2] = &token_id_misc,
	[3] = &token_id_misc,
	[4] = &token_id_misc,
	[5] = &token_id_misc,
	[6] = &token_id_misc,
	};

	node->id = get_char_id(inp[(*pos)]);
	func[node->id](inp, pos, node->id);
	node->str = ft_substr(inp, start_pos, (*pos - start_pos));
}

t_token	*lexer(const char *inp)
{
	size_t	current_pos;
	t_token	*top;
	t_token	*node;

	top = NULL;
	current_pos = 0;
	while (inp[current_pos])
	{
		node = list_token_new();
		if (!node)
			minishell_error("lexer/lexer.c: lexer @ malloc");
		get_token_info(inp, &current_pos, node);
		list_token_add_back(&top, node);
	}
	return (top);
}

/*
 * considering variable expansion:
 *
 * 		export CD="c d ef"; echo ab$CD"g"
 * 		argv would show:
 * 		argv[1] = "abc"
 * 		argv[2] = "d"
 * 		argv[3] = "efg"
 * 		argv[4] = NULL
 *
 * implying some part of expansion happens before parsing or lexigng.
 * however further testing show that the tokens that are added,
 * show up as WORD tokens
 *
 * 		VAR="cat|"; <Makefile $VAR cat >>out
 * 		bash: cat|: command not found
 *
 * 		bash-3.2$ VAR="cat |"; <Makefile $VAR cat >>out
 * 		cat: |: No such file or directory
 * 		cat: cat: No such file or directory
 *
 * add a jumptable for token_id_specific functions.
 * 


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
