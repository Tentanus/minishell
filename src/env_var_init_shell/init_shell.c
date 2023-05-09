/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_shell.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:23:59 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/09 10:24:36 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** this file contains functions to initiate
** a list of environment variables.
** it can be used everytime a new shell or child process is initiated.
**
** Whenever a new chill shell is created, the parent shell copies the
** exported variables and their values.
**
** environment variables are copied from char **envp to a linked list.
** enivornment variable SHLVL is updated.
** enivornment variable OLDPWD is unset.
*/

/*
** function that updates environment variable "SHLVL"
** in list of environment variables
*/
int	init_shell_update_shlvl(t_env_var_ll **env_var_list)
{
	t_env_var_ll	*shlvl_node;
	unsigned int	value;

	shlvl_node = env_var_get_env_node("SHLVL", *env_var_list);
	if (shlvl_node)
	{
		value = ft_atoi(shlvl_node->value) + 1;
		if (shlvl_node->value)
			free(shlvl_node->value);
		shlvl_node->value = ft_itoa(value);
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
** it also sets the SHLVL and unsets OLDPWD.
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
	unset_env_var("OLDPWD", &env_var_list);
	mini->env_list = env_var_list;
	return (0);
}
