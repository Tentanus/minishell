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
# include <signal.h> // for signals
# include <sys/ioctl.h> // for ioctl
# include <termios.h> // for termios

# include <libft.h> // for libft

//			MACROS

# define MARSH_PROMPT "\001\033[1;32m\002marsh> \001\033[0m\002"
# define MARES_PROMPT "\001\033[1;32m\002maresiscoding> \001\033[0m\002"
# define OCTO_PROMPT "\001\033[1;32m\002🐙> \001\033[0m\002"

# define SET_DELIMETER "-|\'\"><$ "

# define MALLOC_ERROR -2
# define ERROR -1
# define SUCCESS 0
# define READ 0
# define WRITE 1

//			GLOBAL


//			E_NUMS

typedef enum e_token_id {
	TOKEN = 0,
	PIPE,
	QUOTE,
	DQUOTE,
	GREAT,
	LESS,
	SH_VAR,
	SPACEBAR,
	WORD
}	t_token_id;

typedef enum e_redir_id {
	REDIR = 0,
	IN,
	HERE,
	OUT,
	APP
}	t_redir_id;

//			STRUCTURES

typedef struct s_token
{
	t_token_id		id;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_redir_id		redir;
	int				fd;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env_var_ll
{
	char				*name;
	char				*value;
	bool				has_value;
	struct s_env_var_ll	*next;
}				t_env_var_ll;

typedef struct s_minishell
{
	char			*input;
	t_token			*token;
	t_token			*syntax;
	t_cmd			*cmd_list;
	t_env_var_ll	*env_list;
	struct termios	saved_term;
}	t_minishell;

typedef struct s_status
{
	// int		status;
	// int		pid;
	char	*exit_str;
}	t_status;

//				GLOBAL VARIABLES

extern t_status	g_status;

//				FUNCTIONS

void			minishell_error(const char *loc);
void			minishell_error_exit(const char *loc);

void			mini_error_test(void  (*func)(const char *), int, const char *str);
void			mini_exit_test(void  (*func)(const char *), int, const char *str);
void			mini_exit_here_test(void (*func)(const char *), int status, const char *str);

void			minishell_quote_error(void);
void			syntax_error(const char *token);

void			error(const char *cmd);
void			cmd_error(const char *cmd);
void			error_print(const char *str);
void			chdir_error(const char *cmd);
void			export_error(const char *name);

//				FUNCTION: STATUS

void			status_update(unsigned int status);

//				FUNCTION: COMPLEX

void			complexer(t_minishell *mini);

//				FUNCTION: LEXER

t_token			*lexer(const char *inp);
t_token_id		get_char_id(const char c);
void			token_id_pipe(const char *inp, size_t *pos, const t_token_id val);
void			token_id_quote(const char *inp, size_t *pos, const t_token_id val);
void			token_id_redir(const char *inp, size_t *pos, const t_token_id val);
void			token_id_shvar(const char *inp, size_t *pos, const t_token_id val);
void			token_id_misc(const char *inp, size_t *pos, const t_token_id val);

//				FUNCTION: SYNTAX

t_token			*syntax(t_token *top, t_env_var_ll *env_list);
t_token			*skip_space_token(t_token *t_cur);
bool			syntax_id_pipe(t_token *t_prev, t_token *t_cur, \
		t_env_var_ll *env_list);
bool			syntax_id_redir(t_token *t_prev, t_token *t_cur, \
		t_env_var_ll *env_list);
bool			syntax_id_misc(t_token *t_prev, t_token *t_cur, \
		t_env_var_ll *env_list);

//				FUNCTION: EXPANDER 

t_token			*expander(t_token *t_input, t_env_var_ll *env_var_list);
char			*expander_get_shell_var(const char *str, const int pos, \
				size_t *len_sh_var, t_env_var_ll *env_var_list);

//				FUNCTION: APPENDER

bool			appender(t_minishell *mini);

//				FUNCTION: PARSER

t_cmd			*parser(t_minishell *mini);
t_token			*parser_id_pipe(t_cmd *cmd_node, t_token *t_current);
t_token			*parser_id_redir(t_cmd *cmd_node, t_token *t_current);
t_token			*parser_id_word(t_cmd *cmd_node, t_token *t_current);
t_token			*parser_id_space(t_cmd *cmd_node, t_token *t_current);

//				HERE_DOC

int				handle_here_doc(t_cmd *cmd_list, t_env_var_ll *list_env);
void			close_here_doc(t_cmd *cmd_list);
void			handle_redirect(t_redir *redir_cur, void (*err_func)(void (*func)(const char *), int status, const char *));

void			redir_error_exit(const char *file);
void			redir_error(const char *file);

//					UTILS_TOKEN

t_token			*list_token_new(void);
t_token			*list_token_cpy_node(t_token *t_node);
t_token			*list_token_last(t_token *t_list);
t_token			*list_token_skip_space(t_token *t_current);
t_token			*list_token_skip_pipe(t_token *t_current);
void			list_token_add_back(t_token **list, t_token *node);

void			list_token_free_list(t_token *t_list, t_token *(*f)(t_token *));
void			list_token_free_last(t_token *t_list, t_token *(*f)(t_token *));
t_token			*list_token_free_node(t_token *t_list);
t_token			*list_token_free_node_non_word(t_token *t_list);
t_token			*list_token_free_node_str(t_token *t_list);

//				FUNCTION: UTILS_CMD

t_cmd			*list_cmd_new(void);
t_cmd			*list_cmd_last(t_cmd *t_list);
void			list_cmd_add_back(t_cmd **cmd_list, t_cmd *cmd_node);

void			list_cmd_free_list(t_cmd *cmd_list);
t_cmd			*list_cmd_free_node(t_cmd *cmd_node);

//				FUNCTION: UTILS_REDIR

t_redir			*list_redir_new(void);
void			list_redir_add_back(t_redir **redir_list, t_redir *redir_node);

void			list_redir_free_list(t_redir *redir_list);
t_redir			*list_redir_free_node(t_redir *redir_node);

//		TEST FUNCTIONS (CAN BE REMOVED)
void			list_token_print(t_token *top);
void			list_cmd_print(t_cmd *cmd_list);

bool			builtin_check(char *cmd);
int				builtin_execute(t_cmd *cmd, t_env_var_ll **env_var_list);
int				builtin_echo(t_cmd *cmd, int fd);
bool			builtin_echo_is_n_option(char *str);
int				builtin_cd(t_cmd *cmd, t_env_var_ll **env_var_list);
char			*builtin_cd_get_new_working_dir(t_cmd *cmd, t_env_var_ll **env_var_list);
int				builtin_pwd(int fd);
int				builtin_export(t_cmd *cmd, t_env_var_ll **env_var_list);
void			builtin_export_print_export(t_env_var_ll *env_var_list);
int				builtin_unset(t_cmd *cmd, t_env_var_ll **env_var_list);
int				unset_env_var(char *name, t_env_var_ll **env_var_list);
int				builtin_env(t_env_var_ll *env_var_list);
int				builtin_exit(t_cmd *cmd);

//				FUNCTION: INIT SHELL

int				init_shell(char **envp, t_minishell *mini);
int				init_shell_update_SHLVL(t_env_var_ll **env_var_list);

//				FUNCTION: ENVIRONMENT VARIABLES

void			env_var_print_linked_list(t_env_var_ll *env_var_list); // TEST FUNCTION (CAN BE REMOVED)
void			env_var_free_node(t_env_var_ll *env_var_node);
void			env_var_free_list(t_env_var_ll *env_var_list);
t_env_var_ll	*env_var_init_node(void);
t_env_var_ll	*env_var_create_new_node(char *env_var_str);
void			env_var_add_to_end_list(t_env_var_ll **env_var_list, t_env_var_ll *new_env_var);
bool			env_var_exists(char *name, t_env_var_ll *env_var_list);
char			*env_var_get_env(char *name, t_env_var_ll *env_var_list);
t_env_var_ll	*env_var_get_env_node(char *name, t_env_var_ll *env_var_list);
void			env_var_set_env(char *envar, t_env_var_ll **env_var_list);
char			**env_var_to_cpp(t_env_var_ll *env_list);
bool			env_var_validate_name(char *name);

// 				FUNCTION: EXECUTOR

void			wait_function(pid_t pid, int count_childs);
void			set_back_std_fd(int tmp_fd_in, int tmp_fd_out);
void			execute_single_command(t_minishell *mini);
void			execute_multiple_commands(t_minishell *mini);
int				handle_builtin(t_cmd *cmd, t_minishell *mini);
void			handle_non_builtin(t_cmd *cmd, t_minishell *mini);
void			executor(t_minishell *mini);

// 				FUNCTION: SIGNALS

void			sig_quit_handler(t_minishell *mini);
void			sig_int_handler(int sig);
void			init_signals(void);

// 				FUNCTION: TMP_MARES (CAN BE REMOVED)

void			mini_parse_input(char *input, t_cmd *cmd);
char			**make_double_array(int word_count);
int				ft_word_counter(char const *s, char c);
void			free_double_array(char **double_array);

//				TEST FUNCTIONS (SHOULD BE REMOVED) // ! NOT NORM PROOF

void			list_token_print(t_token *top);
void			list_cmd_print(t_cmd *cmd_list);

#endif
