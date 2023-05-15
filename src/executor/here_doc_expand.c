/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_expand.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 14:49:58 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/15 19:22:35 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	if (!new_line)
		return (free(line), NULL);
	ft_strlcpy(new_line, line, *pos + 1);
	if (!env_value)
	{
		ft_strlcat(new_line, line + *pos + env_key_len, \
				ft_strlen(new_line) + ft_strlen(line + *pos + env_key_len) + 1);
		return (free(line), new_line);
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
		if (!line[i])
			break ;
		if (line[i] == '$')
			continue ;
		i++;
	}
	return (line);
}

// cause leaks [$VAR doesnt not exits as env var]:
//  > $VAR$VAR
//  > $VAR $VAR
