#include <minishell.h>

typedef int	(*t_redir_func) (t_redir *redir_node);

int	redir_id_input(const char *file)
{
	
}

void			handle_redir(t_cmd *cmd_list)
{
	const t_delimiter_func	func[5] = {
	[0] = NULL,
	[1] = redir_id_input,
	[2] = redir_id_here,
	[3] = redir_id_output,
	[4] = redir_id_append
	};

	while (cmd_list != NULL)
	{
		redir_list = cmd_list->redir
		while (redir_list != NULL)
		{
			error = func[redir_node->redir](redir_node->file);
			redir_list = redir_list->next;
		}
		cmd_list = cmd_list->next;
	}
}
