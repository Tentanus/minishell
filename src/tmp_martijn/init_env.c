#include <minishell.h>

int	init_env_shlvl(t_env_var_ll **env_list) //should this be a **?
{
	t_env_var_ll	*env_shlvl;
	unsigned int	value;

	env_shlvl = list_env_get_node("SHLVL", *env_list);
	if (env_shlvl)
	{
		value = ft_atoi(env_shlvl->value) + 1;
		env_shlvl->value = ft_itoa(value);
		if (!env_shlvl->value)
			return (1);
		return (0);
	}
	env_shlvl = list_env_fill_new("SHLVL=1");
	if (!env_shlvl)
		return (1);
	list_env_add_back(env_list, env_shlvl);
	return (0);
}

/*
** function that adds a environment variable for every envp to our linked list of env vars
*/
//int	init_shell(char **envp, t_minishell *mini)
int	init_env(char **envp, t_minishell *mini)
{
	t_env_var_ll	*env_list;
	t_env_var_ll	*env_node;
	int				i;

	env_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		env_node = list_env_fill_new(envp[i]);
		if (!env_node)
			return (list_env_free_list(env_list), 1);
		list_env_add_back(&env_list, env_node);
		i++;
	}
	if (init_env_shlvl(&env_list))
		return (list_env_free_list(env_list), 1);
	builtin_unset("OLDPWD", &env_list);
//	init_shell_set_underscore(&env_list); is not required by subject
	mini->env_list = env_list;
	return (0);
}

