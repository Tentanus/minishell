#include <minishell.h>

typedef int	(*t_redir_func)(const char *file, int fd, \
			void (err_func)(const char *));

void	redir_error_exit(const char *file)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	exit(errno);
}

void	redir_error(const char *file)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
}

int	redir_id_input(const char *file, int fd, void (err_func)(const char *))
{
	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		return (err_func(file), errno);
	if (dup2(fd, STDIN_FILENO) == ERROR)
		return (err_func(file), errno);
	if (close(fd) == ERROR)
		return (err_func(file), errno);
	return (0);
}

int	redir_id_here(const char *file, int fd, void (err_func)(const char *))
{
	(void) file;
	if (dup2(fd, STDIN_FILENO) == ERROR)
		return (err_func(file), errno);
	if (close(fd) == ERROR)
		return (err_func(file), errno);
	return (0);
}

int	redir_id_output(const char *file, int fd, void (err_func)(const char *))
{
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == ERROR)
		return (err_func(file), errno);
	if (dup2(fd, STDOUT_FILENO) == ERROR)
		return (err_func(file), errno);
	if (close(fd) == ERROR)
		return (err_func(file), errno);
	return (0);
}

int	redir_id_append(const char *file, int fd, void (err_func)(const char *))
{
	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == ERROR)
		return (err_func(file), errno);
	if (dup2(fd, STDOUT_FILENO) == ERROR)
		return (err_func(file), errno);
	if (close(fd) == ERROR)
		return (err_func(file), errno);
	return (0);
}

void	handle_redirect(t_redir *redir_cur, void (*err_func)(const char *))
{
	const t_redir_func	func[5] = {
	[0] = NULL,
	[1] = redir_id_input,
	[2] = redir_id_here,
	[3] = redir_id_output,
	[4] = redir_id_append
	};

	if (redir_cur == NULL)
		return ;
	while (redir_cur != NULL)
	{
		func[redir_cur->redir]((const char *)redir_cur->file, redir_cur->fd, \
				err_func);
		redir_cur = redir_cur->next;
	}
}
