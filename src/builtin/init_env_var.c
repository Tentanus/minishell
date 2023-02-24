#include <minishell.h>

/*
** this file contains functions to initiate
** a linked list of environment variables.
** it can be used everytime a new shell or child process is initiated.
*/

/*
** print linked list of environment variables FOR TESTING!
*/
void	print_linked_list(t_env_var_ll *env_var_list)
{
	printf("LINKED LISTOF ENV VARS:\n\n");
	while (env_var_list != NULL)
	{
		printf("%s ", env_var_list->name);
		printf("= ");
		printf("%s ", env_var_list->value);
		printf("%s\n", env_var_list->has_value ? "true" : "false");
		env_var_list = env_var_list->next;
	}
	printf("\n\n");
}

/*
** function that creates a new node containing environment variable in format of NAME=value
** also adds bool with 'has value' = true or false for every node.
*/
t_env_var_ll	*init_new_var(char *env_var)
{
	t_env_var_ll	*new_var;
	int				i;

	new_var = (t_env_var_ll *)malloc(sizeof(t_env_var_ll));
	if (!new_var)
		return (minishell_error("malloc fail init_new_var"), NULL);
	i = 0;
	if (ft_strchr(env_var, '=') != NULL) 
	{
		while (env_var[i])
		{
			if (env_var[i] == '=')
			{
				new_var->name = ft_substr(env_var, 0, i);
				new_var->value = ft_substr(env_var, i + 1, ft_strlen(env_var));
				break ;
			}
			i++;			
		}
		new_var->has_value = true;
	}
	else
	{
		new_var->name = env_var;
		new_var->value = NULL;
		new_var->has_value = false;
	}
	new_var->next = NULL;
	return (new_var);
}

/*
** function that adds a new node containing a new environment variable in format of NAME=value
** to the end of the linked list of environment variables.
*/
int	add_var_to_end_list(t_env_var_ll **env_var_list, t_env_var_ll *new_var)
{
	t_env_var_ll	*current;

	current = *env_var_list;
	if (*env_var_list == NULL)
		*env_var_list = new_var;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_var;
	}
	new_var->next = NULL;
	return (0);
}

/*
** function that initiates the creation of a new node containing a new environment variable in format of NAME=value
** and calls a function to add this node to the end of the linked list of environment variables.
*/
int	add_variable(char *env_var, t_env_var_ll **env_var_list)
{
	t_env_var_ll	*new_var;

	new_var = init_new_var(env_var);
	if (!new_var)
		return (minishell_error("fail in add_variables"), 1);
	// positie van var in list?
	add_var_to_end_list(env_var_list, new_var);
	// print_linked_list(env_var_list);
	// of add_var_to_list();
	return (0);
}

/*
** function that adds a environment variable for every envp to our linked list of env vars
*/
int	init_env_var(char **envp, t_env_var_ll **env_var_list)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (add_variable(envp[i], env_var_list) == 1)
			return (minishell_error("fail in init_env_var"), 1);
		i++;
	}
	// !!!
	// make new function?
	// SHLVL should be updated:
	// loop through env_var_list and strncmp for env_var_list->name == 'SHLVL='
	// save env_var_list->value
	// remove node and add new node
	// OR update current node with value += 1 (using atoi and itoa?)
	// think about memory when updating SHLVL from 9 to 10 etc
	// !!!
	return (0);
}
