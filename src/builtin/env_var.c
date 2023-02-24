#include <minishell.h>

/*
** This file contains functions to manage and change environment variables.
**
** - function to print all environment variables (env builtin)
**
** - bool function to check if environment variable already exists
**
** - our own getenv function: if env_var with NAME exists, it's VALUE is returned
** 
** - our own setenv function: it sets a (new) environment variable
**
** - function to remove environment variable (unset builtin)
**
** - function to export variable (export)
**
*/

// function to print environment variables stored in linked list
void	print_env(t_env_var_ll *env_var_list)
{
	while (env_var_list != NULL)
	{
		printf("%s", env_var_list->name);
		printf("=");
		printf("%s", env_var_list->value);
		printf("\n");
		env_var_list = env_var_list->next;
	}
}

// bool function to check if environment variable already exists, NOT making use of getenv()
bool	env_var_exists(char *name, t_env_var_ll *env_var_list)
{
	int	len_name;

	len_name = ft_strlen(name);
	while (env_var_list->next != NULL)
	{
		if (ft_strncmp(env_var_list->name, name, len_name) == 0)
			return (true);
		env_var_list = env_var_list->next;
	}
	if (ft_strncmp(env_var_list->name, name, len_name) == 0)
			return (true);
	else
		return (false);
}

// our own getenv function:
// the NAME of the environment variable is search in env_var_list
// if env_var exists, it's VALUE is returned
char	*get_env(char *name, t_env_var_ll *env_var_list)
{
	int		len_name;

	len_name = ft_strlen(name);
	if (env_var_exists(name, env_var_list) == true)
	{
		while (env_var_list->next != NULL)
		{
			if (ft_strncmp(env_var_list->name, name, len_name + 1) == 0)
				return (env_var_list->value);
			env_var_list = env_var_list->next;
		}
	}
	return (NULL);
}

// our own setenv() function: it sets a (new) environment variable
void	set_env(char *envar, t_env_var_ll **env_var_list)
{
	int				len_name;
	t_env_var_ll	*new_var;
	t_env_var_ll	*current = *env_var_list;
	t_env_var_ll	*prev = NULL;

	// MAKE NEW NODE
	new_var = init_new_var(envar);
	len_name = ft_strlen(new_var->name);
	if (env_var_exists(new_var->name, *env_var_list) == true)
	{
		// REMOVE BY NAME:
		// look for node with name
		while (current->next != NULL && ft_strncmp(current->name, new_var->name, len_name) != 0)
		{
			prev = current;
			current = current->next;
				// delete/ free node with variable name
				// add new env_var at that node place
				// make sure list is connected again
		}
		// if node / env_var to replace is not found, return NULL (extra control)
		if (current == NULL)
			return ;
		// let new_var->next point to next element in list
		new_var->next = current->next;
		// free old node
		if (prev == NULL)
			*env_var_list = new_var;
		else
			prev->next = new_var;
		free(current);
	}
	if (env_var_exists(new_var->name, *env_var_list) == false)
	{
		// ADD NODE WITH NEW VARIABLE TO END OF LIST
		add_var_to_end_list(env_var_list, new_var);
	}
}

// function to remove environment variable (unset builtin)
void	unset_env(char *name, t_env_var_ll **env_var_list)
{
	int				len_name;
	t_env_var_ll	*current = *env_var_list;
	t_env_var_ll	*temp_var = NULL;

    // error: bash: unset: `USER=mverbrug': not a valid identifier
	len_name = ft_strlen(name);
	if (env_var_exists(name, *env_var_list) == true)
	{
		// REMOVE BY NAME:
		// look for node with name
		while (current->next != NULL && ft_strncmp(current->next->name, name, len_name) != 0)
		{
			current = current->next;
		}
		// save element we want to remove in temp pointer
    	temp_var = current->next;
		// set previous node's next pointer to point to the node after the node we wish to delete
    	current->next = temp_var->next;
    	// free temp element
		free(temp_var);
	}
	else
		return ;
}

// void	unset_env(char *name, t_env_var *envars)
// {
// 	char	**new_envp;
// 	int		size_of_array;
// 	int		i;
// 	int		j;

// 	size_of_array = get_end_of_envp_list(envars->our_envp) + 1;
// 	new_envp = (char **)malloc(size_of_array * sizeof(char *));
// 	if (!new_envp) // protect malloc!
// 	{
// 		minishell_error("malloc fail unset_env");
// 		exit(1);
// 	}
// 	i = 0;
// 	j = 0;
// 	while(envars->our_envp[i] != NULL)
// 	{
// 		if (i == search_for_env_index(name, envars->our_envp))
// 			j++;
// 		new_envp[i] = ft_strdup(envars->our_envp[j]);
// 		i++;
// 		j++;
// 	}
// 	new_envp[i] = NULL;
// 	free_double_array(envars->our_envp);
// 	envars->our_envp = new_envp;
// 	return ;
// }

// function to export variable (export)

