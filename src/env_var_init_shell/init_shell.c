#include <minishell.h>

/*
** this file contains functions to initiate
** a linked list of environment variables.
** it can be used everytime a new shell or child process is initiated.
**
** Whenever a new chill shell is created, the parent shell copies the
** exported variables and their values.
*/

void	init_shell_set_underscore(t_env_var_ll **env_var_list)
{
	char	*new_path;

	new_path = ft_strjoin("_=", "./minishell"); // ! MALLOC
	if (!new_path)
		return (minishell_error("malloc error new_path in set_underscore"));
	env_var_set_env(new_path, env_var_list);
	free(new_path);
}
/*
** function that updates environment variable "SHLVL" in list of environment variables
*/
int	init_shell_update_SHLVL(t_env_var_ll **env_var_list)
{
	t_env_var_ll	*shlvl_node;
	unsigned int	value;
	
	shlvl_node = env_var_get_env_node("SHLVL", *env_var_list);
	if (shlvl_node)
	{
		value = ft_atoi(shlvl_node->value) + 1;
		if (shlvl_node->value)
			free(shlvl_node->value); // ! FREE previous value
		shlvl_node->value = ft_itoa(value); // ! malloc in ft_itoa
		if (!shlvl_node->value)
			return (1);
		return (0);
	}
	shlvl_node = env_var_create_new_node("SHLVL=1");
	if (!shlvl_node)
		return (1);
	env_var_add_to_end_list(env_var_list, shlvl_node);
	return (0);
}

/*
** function that, for every envp, initiates the creation of a new node
** containing a new environment variable in format of NAME=value
** and adds this to our linked list of environment variables.
** it also sets the SHLVL, unsets OLDPWD,
** and sets _ to our executable name (= last entered command)
*/
int	init_shell(char **envp, t_minishell *mini)
{
	t_env_var_ll	*env_var_list;
	t_env_var_ll	*new_env_var;
	int				i;

	env_var_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new_env_var = env_var_create_new_node(envp[i]);
		if (!new_env_var)
			return (env_var_free_list(env_var_list), 1);
		env_var_add_to_end_list(&env_var_list, new_env_var);
		i++;
	}
	if (init_shell_update_SHLVL(&env_var_list))
		return (env_var_free_list(env_var_list), 1);
	builtin_unset("OLDPWD", &env_var_list);
	init_shell_set_underscore(&env_var_list);
	mini->env_list = env_var_list;
	return (0);
}

// initializing env_var / shell:
// - (check) copy env_var from envp
// - (check) update update_SHLVL
// - (check) unset env_var OLDPWD
// - (check but MAY NEED WORK TODO) update env_var '_'

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