/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 14:48:03 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/15 19:20:27 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	here_lines(const char *delim, int fd, t_env_var_ll *list_env)
{
	char	*line;

	if (!delim)
		mini_exit_child(error_print, -1, \
			"warning: here-doc expected end-of-file");
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			_exit (133);
		line = here_expand(line, list_env);
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	_exit(0);
}

int	here_return(int status, int fd)
{
	if (WEXITSTATUS(status) == 133)
	{
		status_update(0);
		return (-1);
	}
	if (WIFSIGNALED(status) == true && WTERMSIG(status) == SIGINT)
	{
		status_update(1);
		close(fd);
		return (-1);
	}
	return (fd);
}

int	here_init(const char *delim, t_env_var_ll *list_env)
{
	int	pipe_fd[2];
	int	status;
	int	pid;

	if (pipe(pipe_fd) == ERROR)
		return (ERROR);
	pid = fork();
	if (pid == ERROR)
		return (ERROR);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		here_lines(delim, pipe_fd[1], list_env);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	return (here_return(status, pipe_fd[0]));
}

void	close_here_doc(t_cmd *cmd_list)
{
	t_redir	*redir_node;

	while (cmd_list != NULL)
	{
		redir_node = cmd_list->redir;
		while (redir_node != NULL)
		{
			if (redir_node->redir == HERE)
				close(redir_node->fd);
			redir_node = redir_node->next;
		}
		cmd_list = cmd_list->next;
	}
}

int	handle_here_doc(t_cmd *cmd_list, t_env_var_ll *list_env)
{
	t_redir	*redir_node;

	while (cmd_list != NULL)
	{
		redir_node = cmd_list->redir;
		while (redir_node != NULL)
		{
			if (redir_node->redir == HERE)
				redir_node->fd = here_init(redir_node->file, list_env);
			if (redir_node->redir == HERE && redir_node->fd == ERROR)
				return (-1);
			redir_node = redir_node->next;
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}
