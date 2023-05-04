#include <minishell.h>

/*
** our own unset function: it removes environment variable (unset builtin)
*/

// function to remove environment variable (unset builtin)
int	unset_env_var(char *name, t_env_var_ll **env_var_list)
{
	int				len_name;
	t_env_var_ll	*current;
	t_env_var_ll	*temp_var;

	if (!name) // seg fault protection ??
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
	return (SUCCESS); // variable name not found thus not unset!
}

int	builtin_unset(t_cmd *cmd, t_env_var_ll **env_var_list)
{
	int				len_name;
	int				i;
	t_env_var_ll	*current;
	t_env_var_ll	*temp_var;

	current = *env_var_list;
	temp_var = NULL;
	i = 1;
	len_name = ft_strlen(cmd->args[i]);
	while (cmd->args[i] != NULL)
	{
		while (current != NULL && current->next != NULL)
		{
			if (ft_strncmp(current->next->name, cmd->args[i], len_name) == 0)
			{
				temp_var = current->next;
				current->next = temp_var->next;
				env_var_free_node(temp_var);
				break ;
			}
			current = current->next;
		}
		i++;
	}
	return (SUCCESS); // variable name not found thus not unset!
}

