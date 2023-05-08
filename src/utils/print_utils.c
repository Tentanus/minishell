/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:41:55 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/08 15:42:37 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TESTING FUNCTION

size_t	list_cmd_size(t_cmd *t_list);
size_t	list_token_size(t_token *t_list);
void	print_cpp_array(const char **arg);
void	list_redir_print(t_redir *redir_list);

void	list_token_print(t_token *top)
{
	int			size;
	const int	con = list_token_size(top);
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
	};

	size = list_token_size(top);
	printf("\n\t-=-  TOKEN PRINT [%d] -=-\n", con);
	while (size--)
	{
		printf("TOKEN [%02d]\tid: %s [%d]\n\t\tstr: |%s|\n", \
				(con - size), token_name[top->id], top->id, top->str);
		top = top->next;
	}
	return ;
}

void	list_cmd_print(t_cmd *cmd_list)
{
	int			size;
	const int	con = list_cmd_size(cmd_list);

	size = list_cmd_size(cmd_list);
	printf("\nPRINT CMD LIST\t %02d NODES\n", size);
	while (cmd_list != NULL)
	{
		ft_printf("| CMD NODE [%d]:\n", (con - --size));
		print_cpp_array((const char **)cmd_list->args);
		list_redir_print(cmd_list->redir);
		cmd_list = cmd_list->next;
		ft_printf("|______________________\n\n");
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
	};

	if (redir_list == NULL)
	{
		ft_printf("| NO REDIRECTIONS\n");
		return ;
	}
	ft_printf("| REDIRECTIONS:\n");
	while (redir_list != NULL)
	{
		ft_printf("|\tTYPE [%d]:\t%s\n", redir_list->redir, \
				redir_name[redir_list->redir]);
		ft_printf("|\tFILE:\t%s\n", redir_list->file);
		redir_list = redir_list->next;
	}
}

void	print_cpp_array(const char **arg)
{
	size_t	i;

	i = 0;
	printf("| ARGUMENTS:\n");
	while (arg[i] != NULL)
	{
		printf("|\targ [%02zu]:\t%s\n", i, arg[i]);
		i++;
	}
}

size_t	list_token_size(t_token *t_list)
{
	size_t	ret;

	ret = 0;
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
	size_t	ret;

	ret = 0;
	if (t_list == NULL)
		return (0);
	while (t_list != NULL)
	{
		t_list = t_list->next;
		ret++;
	}
	return (ret);
}

/*
** print linked list of environment variables FOR TESTING!
*/
void	env_var_print_linked_list(t_env_var_ll *env_var_list)
{
	printf("LINKED LISTOF ENV VARS:\n\n");
	while (env_var_list != NULL)
	{
		printf("%s", env_var_list->name);
		printf("=");
		printf("%s\n", env_var_list->value);
		env_var_list = env_var_list->next;
	}
}
