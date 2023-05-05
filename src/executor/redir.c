#include <minishell.h>

typedef int	(*t_redir_func)(const char *file, int fd, void (err_func)(void (*f)(const char *), int status, const char *));

int	redir_id_input(const char *file, int fd, void (err_func)(void (*f)(const char *), int status, const char *))
{
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err_func(error, 1, file), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (err_func(error, 1, file), -1);
	if (close(fd) == -1)
		return (err_func(error, 1, file), -1);
	return (0);
}

int	redir_id_here(const char *file, int fd, void (err_func)(void (*f)(const char *), int status, const char *))
{
	(void) err_func;
	(void) file;
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	redir_id_output(const char *file, int fd, void (err_func)(void (*f)(const char *), int status, const char *))
{
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (err_func(error, 1, file), -1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (err_func(error, 1, file), -1);
	if (close(fd) == -1)
		return (err_func(error, 1, file), -1);
	return (0);
}

int	redir_id_append(const char *file, int fd, void (err_func)(void (*f)(const char *), int status, const char *))
{
	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (err_func(error, 1, file), -1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (err_func(error, 1, file), -1);
	if (close(fd) == -1)
		return (err_func(error, 1, file), -1);
	return (0);
}

void	handle_redirect(t_redir *redir_cur, void (*err_func)(void (*func)(const char *), int status, const char *))
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
		func[redir_cur->redir]((const char *)redir_cur->file, redir_cur->fd, err_func);
		redir_cur = redir_cur->next;
	}
}
