#include <minishell.h>

typedef int	(*t_redir_func)(const char *file, int fd);

/*
	Handles (input and output) redirection
*/
void	child_redir_error(const char *file)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	perror(strerror(errno));
}

int	redir_id_input(const char *file, int fd)
{
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (child_redir_error(file), errno);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (child_redir_error(file), errno);
	close(fd);
	return (0);
}

int	redir_id_here(const char *file, int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		return (child_redir_error(file), errno);
	close(fd);
	return (0);
}

int	redir_id_output(const char *file, int fd)
{
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (child_redir_error(file), errno);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (child_redir_error(file), errno);
	close(fd);
	return (0);
}

int	redir_id_append(const char *file, int fd)
{
	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (child_redir_error(file), errno);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (child_redir_error(file), errno);
	close(fd);
	return (0);
}

void handle_redirect(t_redir *redir_cur)
{
	int					error;
	const t_redir_func	func[5] = {
	[0] = NULL,
	[1] = redir_id_input,
	[2] = redir_id_here,
	[3] = redir_id_output,
	[4] = redir_id_append
	};

	while (redir_list != NULL)
	{
		error = func[redir_list->redir] \
				((const char *)redir_list->file, redir_list->fd);
		if (error)
			exit(EXIT_FAILURE);
		redir_list = redir_list->next;
	}
}
