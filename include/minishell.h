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
# define SET_DELIMETER "|\'\"><$ "

//			E_NUMS

typedef enum e_token_id {
	UNINITIALIZED = -1,
	PIPE,
	QUOTE,
	DQUOTE,
	GREAT,
	LESS,
	SH_VAR,
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

typedef struct s_minishell
{
	t_token	*token;
	t_token	*syntax;
	char	**envp;
	char	*input;
	int		status;
}	t_minishell;

typedef struct s_cmd
{
	char			*simple_cmd;
	char			**args;
	int				amount_of_args;
//	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env_var_ll
{
	char				*name;
	char				*value;
	bool				has_value;
	struct s_env_var_ll	*next;
}				t_env_var_ll;

//				FUNCTIONS

void		minishell_error(const char *loc);
void		minishell_syntax_error(t_token *top, const char *str);

//				FUNCTION: PARSER

void		lexer_parser(t_minishell *mini);

//				FUNCTION: EXPANDER 

t_token		*expander(t_token *t_input, t_env_var_ll *env_var_list);

//				FUNCTION: SYNTAX

t_token		*syntax(t_token *top);

t_token		*skip_space_token(t_token *t_cur);
bool		syntax_id_pipe(const t_token *t_prev, const t_token *t_cur);
bool		syntax_id_redir(const t_token *t_prev, const t_token *t_cur);
bool		syntax_id_misc(const t_token *t_prev, const t_token *t_cur);

//				FUNCTION: LEXER

t_token		*lexer(const char *inp);

t_token_id	get_char_id(const char c);
void		token_id_pipe(const char *inp, size_t *pos, const t_token_id val);
void		token_id_quote(const char *inp, size_t *pos, const t_token_id val);
void		token_id_redir(const char *inp, size_t *pos, const t_token_id val);
void		token_id_shvar(const char *inp, size_t *pos, const t_token_id val);
void		token_id_misc(const char *inp, size_t *pos, const t_token_id val);

//				UTILS_TOKEN

size_t		list_token_size(t_token *t_top);
t_token		*list_token_new(void);
t_token		*list_token_cpy_node(t_token *t_node);
t_token		*list_token_last(t_token *t_list);
t_token		*list_token_free_node(t_token *t_list);
void		list_token_add_back(t_token **list, t_token *node);
void		list_token_free_list(t_token *top);

//		TEST FUNCTIONS (CAN BE REMOVED)
void		list_token_print(t_token *top);

//				FUNCTIONS: BUILTINS
bool			builtin_check(char *cmd);
void			builtin_execute(t_cmd *cmd, t_env_var_ll **env_var_list);
int				builtin_echo(t_cmd *cmd, int fd);
bool			builtin_echo_is_n_option(char *str);
int				builtin_cd(t_cmd *cmd, t_env_var_ll **env_var_list);
char			*builtin_cd_get_new_working_dir(t_cmd *cmd, t_env_var_ll **env_var_list);
int				builtin_pwd(int fd);
void			builtin_export(t_cmd *cmd, t_env_var_ll **env_var_list);
void			builtin_export_print_export(t_env_var_ll *env_var_list);
void			builtin_unset(char *name, t_env_var_ll **env_var_list);
void			builtin_env(t_env_var_ll *env_var_list);
void			builtin_exit(t_cmd *cmd);

//				FUNCTIONS: INIT SHELL
int				init_shell(char **envp, t_env_var_ll **env_var_list);
void			init_shell_set_underscore(t_env_var_ll **env_var_list);
void			init_shell_update_SHLVL(t_env_var_ll **env_var_list);
int				init_shell_add_env_vars(char *env_var, t_env_var_ll **env_var_list);

//				FUNCTIONS: HANDLE ENVIRONMENT VARIABLE LIST
void			env_var_print_linked_list(t_env_var_ll *env_var_list); // FOR TESTING
void			env_var_free_node(t_env_var_ll *env_var_list);
t_env_var_ll	*env_var_init_new_var_node(char *env_var);
int				env_var_add_to_end_list(t_env_var_ll **env_var_list, t_env_var_ll *new_var);

//				FUNCTIONS: ENVIRONMENT VARIABLES
bool			env_var_exists(char *name, t_env_var_ll *env_var_list);
char			*env_var_get_env(char *name, t_env_var_ll *env_var_list);
void			env_var_set_env(char *envar, t_env_var_ll **env_var_list);

// 				FUNCTIONS: EXECUTOR

// 				FUNCTIONS: TMP_MARES
void			mini_parse_input(char *input, t_cmd *cmd);
char			**make_double_array(int word_count);
int				ft_word_counter(char const *s, char c);
void			free_double_array(char **double_array);

//					UTILS

#endif
