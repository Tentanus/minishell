#ifndef MINISHELL_H
# define MINISHELL_H

//			INCLUDES

# include <stdio.h> // for printf (and partly readline)
# include <unistd.h> // for close, write, access, dup2, execve, fork, pipe, getcwd, chdir
# include <stdlib.h> // for free, exit, malloc, getenv
# include <readline/readline.h> // for readline
# include <readline/history.h> // for history
# include <stdbool.h> // for bool
# include <fcntl.h> // for open
# include <string.h> // for strerror
# include <errno.h> // for errors
# include <sys/wait.h> // for waitpid

# include <libft.h> // for libft

//			MACROS

# define MARSH_PROMPT "\001\033[1;32m\002marsh-0.1> \001\033[0m\002"
# define MARES_PROMPT "\001\033[1;32m\002Maresiscoding> \001\033[0m\002"

//			E_NUMS

typedef enum e_token_id {
	UNINITIALIZED = -1,
	QUOTE,
	DQUOTE,
	PIPE,
	GREAT,
	LESS,
	SPACEBAR,
	WORD
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
	char			*simple_cmd;
	char			**args;
	int				amount_of_args;
//	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

// typedef struct s_env{
// 	char			*OLDPWD;
// 	char			*PWD;
// }				t_env;

// typedef struct s_env_list{
// 	char				*key;
// 	char				*value;
//	struct s_env_list	*next;
// }				t_env_list;

//			FUNCTIONS

void	minishell_error(const char *loc);
void	minishell_syntax_error(t_token token);

//				FUNCTION: PARSER

void		lexer_parser(t_minishell *mini);

//				FUNCTION: SYNTAX

void	syntax_check(t_token *top);
t_token	*skip_space_token(t_token *n_cur);
bool	syntax_id_quote(const t_token *n_prev, const t_token *n_cur);
bool	syntax_id_pipe(const t_token *n_prev, const t_token *n_cur);
bool	syntax_id_redir(const t_token *n_prev, const t_token *n_cur);
bool	syntax_id_space(const t_token *n_prev, const t_token *n_cur);
bool	syntax_id_word(const t_token *n_prev, const t_token *n_cur);

//				FUNCTION: LEXER

t_token		*lexer(const char *inp);
void		get_token_info(const char *inp, size_t *pos, t_token *node);
t_token_id	get_char_id(const char c);
void		token_id_quote(const char *inp, size_t *pos, const t_token_id val);
void		token_id_pipe(const char *inp, size_t *pos, const t_token_id val);
void		token_id_great(const char *inp, size_t *pos, const t_token_id val);
void		token_id_less(const char *inp, size_t *pos, const t_token_id val);
void		token_id_misc(const char *inp, size_t *pos, const t_token_id val);

// void	parse_input(int argc, char **argv, t_cmd *cmd);
void	mini_parse_input(char *input, t_cmd *cmd);
bool	check_builtin(char *cmd);
void	execute_builtin(t_cmd *cmd, char **envp);
char	**make_double_array(int word_count);
int		ft_word_counter(char const *s, char c);
int		execute_echo(t_cmd *cmd, int fd);
int		execute_pwd(int fd);
int		execute_cd(t_cmd *cmd, char **envp);

void	print_env(char **envp);
void	change_pwd_oldpwd(char **envp);

//				UTILS

//				UTILS_TOKEN

int		list_token_size(t_token *top);
t_token	*list_token_new(void);
t_token	*list_token_last(t_token *list);
void	list_token_add_back(t_token **list, t_token *node);

//		TEST FUNCTIONS (CAN BE REMOVED)
void	list_token_print(t_token *top);


#endif
