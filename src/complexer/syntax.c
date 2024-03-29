#include <minishell.h>

typedef bool	(*t_syntax_func) (t_token *t_prev, t_token *t_cur, \
		t_env_var_ll *env_list);

t_token	*list_token_start_nonspace(t_token *list)
{
	if (list == NULL)
		return (NULL);
	if (list->id == SPACEBAR)
		return (list->next);
	return (list);
}

t_token	*syntax(t_token *top, t_env_var_ll *env_list)
{
	t_token				*t_prev;
	t_token				*t_cur;
	const t_syntax_func	func[9] = {
	[0] = NULL,
	[1] = syntax_id_pipe,
	[2] = syntax_id_misc,
	[3] = syntax_id_misc,
	[4] = syntax_id_redir,
	[5] = syntax_id_redir,
	[6] = syntax_id_misc,
	[7] = NULL,
	[8] = syntax_id_misc
	};

	t_prev = NULL;
	t_cur = list_token_start_nonspace(top);
	while (t_cur != NULL)
	{
		if (func[t_cur->id](t_prev, t_cur, env_list))
			return (t_cur);
		t_prev = t_cur;
		t_cur = list_token_skip_space(t_cur);
	}
	return (NULL);
}

// if only space tokens are given wat to do?

/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- 

%token  WORD

%token   DLESS    DGREAT
         '<<'     '>>'    

   -------------------------------------------------------
   The Grammar
   ------------------------------------------------------- 


%start  pipe_sequence
%%
pipe_sequence    :                   command
                 | pipe_sequence '|' command
                 ;
command          : cmd_prefix cmd_name cmd_suffix
                 | cmd_prefix cmd_name
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;
cmd_name         : WORD                     Apply rule 1
                 ;
cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 ;
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;
io_redirect      : '<'       filename
                 | '>'       filename
                 | DGREAT    filename
                 |           io_here
                 ;
filename         : WORD                     Apply rule 2
                 ;
io_here          : DLESS     here_end
                 ;
here_end         : WORD                     Apply rule 3
                 ;

   --------------------------------------------------------- */
