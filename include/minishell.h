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

t_token	*lexer(const char *inp);
void	lex_free(t_token *token);

void	mini_parse_input(char *input, t_cmd *cmd);
char	**make_double_array(int word_count);
int		ft_word_counter(char const *s, char c);

bool	check_builtin(char *cmd);
void	execute_builtin(t_cmd *cmd, char **envp);
int		execute_echo(t_cmd *cmd, int fd);
int		execute_pwd(int fd);
int		execute_cd(t_cmd *cmd, char **envp);

void    print_env(char **envp);
void    set_env(char *name, char *value, char **envp);
int		search_for_env_index(char *name, char **envp);
bool	env_var_exists(char *name);
void	change_pwd_oldpwd(char **envp);


//				UTILS

int		skip_whitespace(const char *str);

//				UTILS_TOKEN

int		list_token_size(t_token *top);
t_token	*list_token_last(t_token *list);
void	list_token_add_back(t_token **list, t_token *node);

//		TEST FUNCTIONS (CAN BE REMOVED)
void	list_token_print(t_token *top);


#endif
