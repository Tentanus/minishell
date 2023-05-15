/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:27:12 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/15 12:55:28 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** our own unset function: it removes environment variable (unset builtin)
*/

void	unset_node(char *env_var, t_env_var_ll **env_var_list)
{
	t_env_var_ll	*current;
	t_env_var_ll	*prev;
	int				len_name;

	prev = NULL;
	current = *env_var_list;
	len_name = ft_strlen(env_var);
	while (current != NULL)
	{
		if (ft_strncmp(current->name, env_var, len_name + 1) == 0)
		{
			if (prev == NULL)
				*env_var_list = current->next;
			else
				prev->next = current->next;
			list_env_var_free_node(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	builtin_unset(t_cmd *cmd, t_env_var_ll **env_var_list)
{
	int				i;

	i = 1;
	if (!cmd->args[1])
		return (ERROR);
	while (cmd->args[i] != NULL)
	{
		if (env_var_validate_name(cmd->args[i]) == false)
		{
			mini_error(unset_error, 1, cmd->args[i]);
			status_update(1);
		}
		else
			unset_node(cmd->args[i], env_var_list);
		i++;
	}
	if (ft_strncmp(g_status, "1", 2) == 0)
		return (ERROR);
	return (SUCCESS);
}
