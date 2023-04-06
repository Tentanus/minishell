#include <minishell.h>

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
			line = here_replace_line(line, &i);
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
		write(pipe_fd[1], line, ft_strlen(line));
		if (!ft_strncmp(line, delim, ft_strlen(delim)))
			break ;
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[o]);
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
