#include <minishell.h>

/*
** our own unset function: it removes environment variable (unset builtin)
*/

// function to remove environment variable (unset builtin)
int	builtin_unset(char *name, t_env_var_ll **env_var_list)
{
	int				len_name;
	t_env_var_ll	*current = *env_var_list;
	t_env_var_ll	*temp_var = NULL;

	if (!name)
		return (ERROR);
	len_name = ft_strlen(name);
	while (current != NULL && current->next != NULL)
	{
		if (ft_strncmp(current->next->name, name, len_name) == 0)
		{
			temp_var = current->next;
			current->next = temp_var->next;
			list_env_free_node(temp_var);
			return (SUCCESS);
		}
		current = current->next;
	}
	return (SUCCESS); // variable name not found thus not unset!
}
