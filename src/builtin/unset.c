#include <minishell.h>

/*
** our own unset function: it removes environment variable (unset builtin)
*/

// function to remove environment variable (unset builtin)
void	builtin_unset(char *name, t_env_var_ll **env_var_list)
{
	int				len_name;
	t_env_var_ll	*current = *env_var_list;
	t_env_var_ll	*temp_var = NULL;

	len_name = ft_strlen(name);
	while (current != NULL)
	{
		if (ft_strncmp(current->next->name, name, len_name) == 0)
		{
			temp_var = current->next;
			current->next = temp_var->next;
			env_var_free_node(temp_var);
			return ;
		}
		current = current->next;
	}
	return ;
}

// void	OLD_unset_env(char *name, t_env_var_ll **env_var_list)
// {
// 	int				len_name;
// 	t_env_var_ll	*current = *env_var_list;
// 	t_env_var_ll	*temp_var = NULL;

//     // error: bash: unset: `USER=mverbrug': not a valid identifier
// 	len_name = ft_strlen(name);
// 	if (env_var_exists(name, *env_var_list) == true)
// 	{
// 		// REMOVE BY NAME:
// 		// look for node with name
// 		while (current->next != NULL && ft_strncmp(current->next->name, name, len_name) != 0)
// 		{
// 			current = current->next;
// 		}
// 		// save element we want to remove in temp pointer
//     	temp_var = current->next;
// 		// set previous node's next pointer to point to the node after the node we wish to delete
//     	current->next = temp_var->next;
//     	// free temp element
// 		env_var_free_node(temp_var);
// 	}
// 	else
// 		return ;
// }