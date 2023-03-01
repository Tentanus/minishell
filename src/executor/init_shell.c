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
** function that initiates the creation of a new node containing a new environment variable in format of NAME=value
** and calls a function to add this node to the end of the linked list of environment variables.
*/
int	init_shell_add_env_vars(char *env_var, t_env_var_ll **env_var_list)
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
void init_shell_update_SHLVL(t_env_var_ll **env_var_list)
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
* $_, an underscore:
* 1. At shell startup, set to the pathname used to invoke the shell.
* When you invoke a new shell, the $_ parameter in the new shell will
* be set to the value of the $_ parameter in the parent shell.
* This means that the $_ parameter in the new shell will contain the
* last argument of the command that invoked the new shell!
TODO ? fix second functionality of $_
* 2. is a special parameter that expands to/contains
* the last argument to the previous simple command that was executed.
* $_ is set automatically by Bash after each command is executed,
* regardless of whether it was successful or not.
* It is often used as a quick way to reference the
* last argument without having to retype it.
* If the previous command didn't have any arguments, $_ will be empty.
* $_ is just a regular parameter like any other, which means you can use it
* in the same way you would use any other parameter.
* For example, you can pass it as an argument to a command,
* or use it in a variable assignment.
* $_ is not an environment variable, which means it is not available
* to programs that are launched from within your Bash session.
*/
void	init_shell_set_underscore(t_env_var_ll **env_var_list)
{
	char	*new_path;

	new_path = ft_strjoin("_=", "./martest"); // change to 'marshell'?
	if (!new_path)
		return (minishell_error("malloc error new_path in set_underscore"));
	set_env(new_path, env_var_list);
	free(new_path);
}


/*
** function that adds a environment variable for every envp to our linked list of env vars
*/
int	init_shell(char **envp, t_env_var_ll **env_var_list)
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
	set_underscore(env_var_list);
	return (0);
}

// initializing env_var / shell:
// - (check) copy env_var from envp
// - (check) update update_SHLVL
// - (check) unset env_var OLDPWD
// - (check but MAY NEED WORK TODO) update env_var '_'