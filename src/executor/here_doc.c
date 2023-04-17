#include <minishell.h>

char	*here_replace_line(char *line, const char *env_value, \
		size_t *pos, size_t env_key_len)
{
	char			*new_line;
	const size_t	env_value_len = ft_strlen(env_value);

	new_line = ft_calloc(sizeof(char), (ft_strlen(line) - env_key_len + \
				env_value_len + 1));
	if (!line)
		return (free(line), NULL);
	ft_strlcpy(new_line, line, *pos + 1);
	ft_strlcat(new_line, env_value, ft_strlen(new_line) + env_value_len + 1);
	ft_strlcat(new_line, line + *pos + env_key_len, \
			ft_strlen(new_line) + ft_strlen(line + *pos + env_key_len) + 1);
	(*pos) += env_value_len;
	free(line);
	return (new_line);
}

char	*here_expand(char *line, t_env_var_ll *list_env)
{
	char	*env_name;
	char	*env_value;
	size_t	i;
	size_t	var_len;

	i = 0;
	while(line[i])
	{
		if (line[i] == '$' && line[i + 1] != '\0')
		{
			var_len = 0;
			token_id_shvar(line + i, &var_len, 0);
			if (var_len <= 1)
			{
				i++;
				continue ;
			}
			env_name = ft_substr(line, i + 1, var_len - 1);
			if (!env_name)
				return (NULL);
			env_value = env_var_get_env(env_name, list_env);
			line = here_replace_line(line, env_value,  &i, var_len);
			if (!line)
				return (NULL);
		}
		i++;
	}
	return (line);
}

int	here_init(const char *delim, t_env_var_ll *list_env)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (-1);
		line = here_expand(line, list_env);
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
			break ;
		line = ft_strjoin_fs1(line, "\n");
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
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

void	handle_here_doc(t_cmd *cmd_list, t_env_var_ll *list_env)
{
	t_redir	*redir_node;

	while (cmd_list != NULL)
	{
		redir_node = cmd_list->redir;
		while (redir_node != NULL)
		{
			if (redir_node->redir == HERE)
				redir_node->fd = here_init(redir_node->file, list_env);
			if (redir_node->redir == HERE && redir_node->fd == -1)
				minishell_error("here_doc fd failed");
			redir_node = redir_node->next;
		}
		cmd_list = cmd_list->next;
	}
}
