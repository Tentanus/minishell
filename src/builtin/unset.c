#include <minishell.h>

/*
** our own unset function: it removes environment variable (unset builtin)
*/

// function to remove environment variable (unset builtin)
int	builtin_unset(char *name, t_env_var_ll **env_var_list)
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
