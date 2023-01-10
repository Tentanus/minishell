#ifndef MINISHELL_H
# define MINISHELL_H

//			INCLUDES

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <libft.h>

//			MACROS

# define SUCCESS 0
# define ERROR -1

# define MARSH_PROMPT "\001\033[1;32m\002marsh-0.1> \001\033[0m\002"

//			E_NUMS

typedef enum e_token_identifiers {
	UNINITIATIED = 0,
	BACK_SLASH,
	DOUB_QUOTE,
	PIPE,
	GREAT,
	LESS,
	CHAR_END
} t_token_identifiers;

//			STRUCTURES

typedef struct s_token{

	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell{
	t_token	*token;
	char	**envp;
	char	*input;
	int		status;
}	t_minishell;


//			FUNCTIONS

t_token	*lexer(const char *inp);

void	lex_free(t_token *token);

//				UTILS

#endif
