#include <minishell.h>

char	*here_replace_line(const char *line, const char env_value, \
		size_t *pos, size_t env_key_len)
{
	char			new_line;
	const size_t	env_value_len = ft_strlen(env_value);

	new_line = malloc(sizeof(char) * (ft_strlen(line) - env_key_len + \
				env_value_len + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(new_line, line, *pos + 1);
	ft_strlcat(new_line, env_value, env_value_len + 1);
	ft_strcpy(new_line, line + *pos + env_value_len, \
			ft_strlen(line + pos + env_key_len));
	return (new_line);
}

char	*here_expand(const char *line, t_env_var_ll *list_env)
{
	char	*ret;
	char	*env_name;
	char	*env_value;
	size_t	i;
	size_t	var_len;

	i = 0;
	while(line[i])
	{
		var_len = 0;
		if (line[i] == '$')
		{
			token_id_shvar(str + i, &var_len, 0);
			env_name = ft_substr(str, i + 1, var_len - 1);
			if (!env_str)
				return (NULL);
			env_value = env_var_get_env(env_name, list_env);
			line = here_replace_line(line, env_value,  &i, var_len);
			if (!line)
				return (NULL);
		}
		i++;
	}
}

void	here_init(const char delim, t_env_var_ll *list_env)
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
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	handle_here(t_cmd *cmd_list, t_env_var_ll *list_env)
{
	while (cmd_list != NULL)
	{
		redir_node = cmd_list->redir;
		while (redir_node != NULL)
		{
			if (redir_node->id == HERE)
				redir_node->fd = here_init(redir_node->file);
			redir_node = redir_node->next;
		}
		cmd_list = cmd_list->next;
	}
}
