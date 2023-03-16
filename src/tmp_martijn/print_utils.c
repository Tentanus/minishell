#include <minishell.h>

// TESTING FUNCTION

size_t	list_cmd_size(t_cmd *t_list);
size_t	list_token_size(t_token *t_list);
void	print_cpp_array(const char **arg);
void	list_redir_print(t_redir *redir_list);

void	list_token_print(t_token *top)
{
	int			size = list_token_size((void *) top);
	const int	con = size;
	const char	*token_name[9] = {
		[0] = "TOKEN",
		[1] = "PIPE",
		[2] = "QUOTE",
		[3] = "DOUBLE QUOTE",
		[4] = "GREAT",
		[5] = "LESS",
		[6] = "SHELL_VAR",
		[7] = "SPACE",
		[8] = "WORD"
	} ;

	printf("\n\t-=-  TOKEN PRINT -=-\n");
	while (size--)
	{
		printf("TOKEN [%02d]\tid:  %s [%d]\n\t\tstr: |%s|\n", (con - size),  token_name[top->id], top->id, top->str);
		top = top->next;
	}
	return ;
}

void	list_cmd_print(t_cmd *cmd_list)
{
	int			size = list_cmd_size( cmd_list);
	const int	con = size;

	ft_printf("\n\t-=-  PRINT CMD LIST -=-\n");
	   printf("\t-=-  %02d NODES -=-\n", size);
	while (cmd_list != NULL)
	{
		   printf("CMD NODE [%02d]", (con - size));
		ft_printf("PATH:\t%s\n", cmd_list->simple_cmd);
		print_cpp_array((const char **)cmd_list->args);
		list_redir_print(cmd_list->redir);
		cmd_list = cmd_list->next;
	}
	ft_printf("\n\t-=- PRINT FINISHED -=-\n");
}

void	list_redir_print(t_redir *redir_list)
{
	const char	*redir_name[5] = {
		[0] = "REDIR",
		[1] = "INPUT",
		[2] = "HERE_DOC",
		[3] = "OUTPUT",
		[4] = "APPEND"
	} ;

	ft_printf("PRINT REDIRECTIONS\n");
	while (redir_list != NULL)
	{
		ft_printf("TYPE:\t%s [%d]\n", redir_name[redir_list->redir], redir_list->redir);
		ft_printf("file:\t%s\n", redir_list->file);
		redir_list = redir_list->next;
	}
}

void	print_cpp_array(const char **arg)
{
	size_t i = 0;

	printf("ARGUMENTS\n");
	while (arg[i] != NULL)
		printf("arg [%02zu]:\t%s\n", i, arg[i]);
}

size_t	list_token_size(t_token *t_list)
{
	size_t	ret = 0;

	if (t_list == NULL)
		return (0);
	while (t_list != NULL)
	{
		t_list = t_list->next;
		ret++;
	}
	return (ret);
}

size_t	list_cmd_size(t_cmd *t_list)
{
	size_t	ret = 0;

	if (t_list == NULL)
		return (0);
	while (t_list != NULL)
	{
		t_list = t_list->next;
		ret++;
	}
	return (ret);
}

