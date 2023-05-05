#include <minishell.h>

char	*here_replace_line(char *line, const char *env_value, \
		size_t *pos, size_t env_key_len)
{
	char	*new_line;
	size_t	env_value_len;

	if (!env_value)
		env_value_len = 0;
	else
		env_value_len = ft_strlen(env_value);
	new_line = ft_calloc(sizeof(char), (ft_strlen(line) - env_key_len + \
				env_value_len + 1));
	if (!line)
		return (free(line), NULL);
	ft_strlcpy(new_line, line, *pos + 1);
	if (!env_value)
	{
		ft_strlcat(new_line, line + *pos + env_key_len, \
				ft_strlen(new_line) + ft_strlen(line + *pos + env_key_len) + 1);
		return (new_line);
	}
	ft_strlcat(new_line, env_value, ft_strlen(new_line) + env_value_len + 1);
	ft_strlcat(new_line, line + *pos + env_key_len, \
			ft_strlen(new_line) + ft_strlen(line + *pos + env_key_len) + 1);
	(*pos) += env_value_len;
	free(line);
	return (new_line);
}

char	*here_expand_line(char *line, size_t pos, t_env_var_ll *list_env)
{
	char	*env_name;
	char	*env_value;
	size_t	var_len;

	var_len = 0;
	token_id_shvar(line + pos, &var_len, 0);
	if (var_len <= 1)
		return (line);
	env_name = ft_substr(line, pos + 1, var_len - 1);
	if (!env_name)
		return (NULL);
	env_value = env_var_get_env(env_name, list_env);
	free(env_name);
	line = here_replace_line(line, env_value, &pos, var_len);
	if (!line)
		return (NULL);
	return (line);
}

char	*here_expand(char *line, t_env_var_ll *list_env)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '\0')
		{
			line = here_expand_line(line, i, list_env);
			if (!line)
				return (NULL);
		}
		i++;
	}
	return (line);
}

int	here_lines(const char *delim, int fd, t_env_var_ll *list_env)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			mini_exit_test(error_print, ERROR, \
					"warning: here-doc expected end-of-file");
		line = here_expand(line, list_env);
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	exit(0);
}

int	here_return(int status, int fd)
{
	if (WIFSIGNALED(status) == true)
	{
		if (WTERMSIG(status) == SIGINT)
			status_update(130);
		close(fd);
		return (ERROR);
	}
	return(fd);
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
				return (mini_error_test(error_print, ERROR, "here_doc fd failed"), ERROR); // ! double check with maarty
			redir_node = redir_node->next;
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}
