#include <minishell.h>

/*
** our own unset function: it removes environment variable (unset builtin)
*/

int	unset_env_var(char *name, t_env_var_ll **env_var_list)
{
	int				len_name;
	t_env_var_ll	*current;
	t_env_var_ll	*temp_var;

	if (!name)
		return (MALLOC_ERROR);
	current = *env_var_list;
	temp_var = NULL;
	len_name = ft_strlen(name);
	while (current != NULL && current->next != NULL)
	{
		if (ft_strncmp(current->next->name, name, len_name) == 0)
		{
			temp_var = current->next;
			current->next = temp_var->next;
			env_var_free_node(temp_var);
			return (SUCCESS);
		}
		current = current->next;
	}
	return (SUCCESS);
}

// int	builtin_unset(t_cmd *cmd, t_env_var_ll **env_var_list)
// {
// 	int				len_name;
// 	int				i;
// 	t_env_var_ll	*current;
// 	t_env_var_ll	*temp_var;

// 	current = *env_var_list;
// 	temp_var = NULL;
// 	i = 1;
// 	if (!cmd->args[1])
// 		return (ERROR);
// 	while (cmd->args[i] != NULL)
// 	{
// 		len_name = ft_strlen(cmd->args[i]);
// 		while (current != NULL && current->next != NULL)
// 		{
// 			if (ft_strncmp(current->name, cmd->args[i], len_name + 1) == 0)
// 			{
// 				temp_var = current;
// 				if (current == *env_var_list)
// 				{
// 					env_var_list = &(current->next);
// 				}
// 				else
// 				{
// 					current->next = temp_var->next;
// 				}
// 				env_var_free_node(temp_var);
// 				current = *env_var_list;
// 				break ;
// 			}
// 			current = current->next;
// 		}
// 		i++;
// 	}
// 	return (SUCCESS);
// }


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
			env_var_free_node(current);
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
