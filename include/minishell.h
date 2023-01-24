#ifndef MINISHELL_H
# define MINISHELL_H

//			INCLUDES
# include <stdio.h> // for printf (and partly readline)
# include <libft.h> // for libft
# include <unistd.h> // for close, write, access, dup2, execve, fork, pipe
# include <stdlib.h> // for free, exit, malloc
# include <readline/readline.h> // for readline
# include <readline/history.h> // for history
# include <stdbool.h> // for bool

# include <fcntl.h> // for open
# include <string.h> // for strerror
# include <errno.h> // for errors
# include <sys/wait.h> // for waitpid

//			MACROS

# define MARSH_PROMPT "\001\033[1;32m\002marsh-0.1> \001\033[0m\002"

//			E_NUMS

typedef enum e_token_id {
	UNINITIALIZED,
	PIPE,
	QUOTE,
	DQUOTE,
	GREAT,
	LESS,
	DGREAT,
	DLESS,
}	t_token_id;

//			STRUCTURES

typedef struct s_token
{
	t_token_id		id;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell{
	t_token	*token;
	char	**envp;
	char	*input;
	int		status;
}	t_minishell;

typedef struct s_cmd{
	char 			*simple_cmd;
	char 			**args;
    int             amount_of_args;
	// t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

//			FUNCTIONS

t_token	*lexer(const char *inp);
void	lex_free(t_token *token);

void	parse_input(int argc, char **argv, t_cmd *cmd);
bool    check_builtin(char *cmd);
void    execute_builtin(t_cmd *cmd);
char	**make_double_array(int word_count);
int		execute_echo(t_cmd *cmd, int fd);

//				UTILS

#endif
