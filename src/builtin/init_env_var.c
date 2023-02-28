#include <minishell.h>

/*
** this file contains functions to initiate
** a linked list of environment variables.
** it can be used everytime a new shell or child process is initiated.
**
** Whenever a new chill shell is created, the parent shell copies the
** exported variables and their values.
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
				// printf("whaddup\n");
				new_var->value = ft_substr(env_var, i + 1, ft_strlen(env_var) - i - 1);
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
** function that updates environment variable "SHLVL" in list of environment variables
*/
void update_SHLVL(t_env_var_ll **env_var_list)
{
	t_env_var_ll	*current = *env_var_list;

	int	value = 0;
	while (current != NULL)
	{
		if (ft_strncmp("SHLVL", current->name, 6) == 0)
		{
			// printf("%s ", current->name);
			// printf("current->value %s \n", current->value);
			value = ft_atoi(current->value) + 1;
			current->value = ft_itoa(value); // ! malloc in ft_itoa
			// printf("new current->value %s \n", current->value);
		}
		current = current->next;
	}
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
	if (env_var_exists("SHLVL", *env_var_list) == true)
		update_SHLVL(env_var_list);
	unset_env("OLDPWD", env_var_list);
	return (0);
}


// initializing env_var / shell:
// - (check) copy env_var from envp
// - (check) update update_SHLVL
// - (check) unset env_var OLDPWD
// ! TO DO: update env_var '_', see link:
// https://unix.stackexchange.com/questions/436615/when-is-an-environment-variable-of-a-bash-shell
