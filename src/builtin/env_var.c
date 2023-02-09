#include <minishell.h>

/*
** This file contains functions to manage and change environment variables.
**
** 1. bool function to check if environment variable already exists
**
** 2. our own getenv function: if env_var with NAME exists, it's VALUE is returned.
** 
** 3. function to get index of env_var with NAME in envp list
**
** 4. function to get index of END of envp list
**
** 5. util function that makes string of format 'NAME=VALUE'
**
** 6. our own setenv function: it sets a (new) environment variable 
**
** 7. function to remove environment variable (unset builtin)
**
** 8. function to print double array / all envps (env builtin)
**
** 9. function to export variable (export)
**
** 10. function for initial copy of char **envp into t_env_var *envars->our_envp
** 
*/

// 1. when making use of getenv()
bool	get_env_var_exists(char *name)
{
	if (getenv(name) != NULL)
		return (true);
	return (false);
}

// 1. when NOT making use of getenv()
bool	env_var_exists(char *name, char **envp)
{
	int	i;
	int	len_name;

	i = 0;
	len_name = ft_strlen(name);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], name, len_name) == 0
			&& ft_strncmp(&envp[i][len_name], "=", 1) == 0)
			return (true);
		i++;
	}
	return (false);
}

// 2. our own getenv function:
// env_var with NAME is given as argument, and is searched for in envars->our_envp
// if env_var exists, it's VALUE is returned: a pointer to the envp after 'NAME='
// no memory is allocated
char	*get_env(char *name, t_env_var *envars)
{
	int		index;
	int		len_name;

	index = 0;
	len_name = ft_strlen(name);
	if (env_var_exists(name, envars->our_envp) == true)
	{
		index = search_for_env_index(name, envars->our_envp);
		return (&envars->our_envp[index][len_name + 1]);
	}
	else
		return (NULL);
}

// 3. returns index of env_var with NAME in envp list
int	search_for_env_index(char *name, char **envp)
{
	int	i;
	int	len_name;

	i = 0;
	len_name = ft_strlen(name);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], name, len_name) == 0
			&& ft_strncmp(&envp[i][len_name], "=", 1) == 0)
			break ;
		i++;
	}
	return (i);
}

// 4. returns index of END of envp list
int		get_end_of_envp_list(char **envp)
{
	int i;
	
	i = 0;
	while(envp[i])
		i++;
	return (i);
}

// 5. util function that makes string of format NAME=VALUE
char	*make_env_var_format(char *name, char *value)
{
	char	*env_var = NULL;
	size_t	env_var_size;

	env_var_size = ft_strlen(name) + ft_strlen(value) + 2;
	env_var = malloc(env_var_size);
	if (!env_var) // protect malloc!
	{
		minishell_error("malloc fail make_env_var_format");
		exit(1);
	}
	// make new env_var of format 'NAME=value'
	ft_strlcpy(env_var, name, env_var_size); // copy name to env_var
	ft_strlcat(env_var, "=", env_var_size); // concatenate name and =
	ft_strlcat(env_var, value, env_var_size); // concatenate name= and value
	return (env_var);
}

// 6. our own setenv() function: it sets a (new) environment variable
void	set_env(char *name, char *value, t_env_var *envars)
{
	char	**new_envp;
	int		size_of_array;
	char	*env_var = NULL;
	int		index_name;
	int		i;

	i = 0;
	env_var = make_env_var_format(name, value);
	if (env_var_exists(name, envars->our_envp) == true)
	{
		index_name = search_for_env_index(name, envars->our_envp);
		free(envars->our_envp[i]);
		envars->our_envp[i] = ft_strdup(env_var);
	}
	if (env_var_exists(name, envars->our_envp) == false)
	{
		size_of_array = get_end_of_envp_list(envars->our_envp) + 2;
		new_envp = (char **)malloc(size_of_array * sizeof(char *));
		if (!new_envp) // protect malloc!
		{
			minishell_error("malloc fail set_env");
			exit(1);
		}
		while(envars->our_envp[i] != NULL)
		{
			new_envp[i] = ft_strdup(envars->our_envp[i]);
			i++;
		}
		new_envp[i] = env_var;
		new_envp[i + 1] = NULL;
		free_double_array(envars->our_envp);
		envars->our_envp = new_envp;
	}
	return ;
}

// 7. function to remove environment variable (unset builtin)
void	unset_env(char *name, t_env_var *envars)
{
	char	**new_envp;
	int		size_of_array;
	int		i;
	int		j;

	size_of_array = get_end_of_envp_list(envars->our_envp);
	new_envp = (char **)malloc(size_of_array * sizeof(char *));
	if (!new_envp) // protect malloc!
	{
		minishell_error("malloc fail unset_env");
		exit(1);
	}
	i = 0;
	j = 0;
	while(envars->our_envp[i] != NULL)
	{
		if (i == search_for_env_index(name, envars->our_envp))
			j++;
		// ft_strlcpy(new_envp[i], envars->our_envp[j], envp_len);
		new_envp[i] = ft_strdup(envars->our_envp[j]);
		i++;
		j++;
	}
	new_envp[i] = NULL;
	free_double_array(envars->our_envp);
	envars->our_envp = new_envp;
	return ;
}

// 8. function to print double char array (like 'char **envp')
// void    print_double_array(char **double_array)
// {
//     int i;
// 	char *s;
    
//     i = 0;
// 	while(double_array[i] != NULL)
// 	{
// 		s = double_array[i];
// 		ft_putstr_fd(s, 1); // change 1 to fd?
// 		ft_putstr_fd("\n", 1); // change 1 to fd?
// 		i++;
// 	}
// 	if (i == 0)
// 		ft_putstr_fd("(null)\n", 1); // change 1 to fd?
//     return ;
// }
void    print_env(char **envp)
{
    int i;
	char *s;
    
    i = 0;
	while(envp[i] != NULL)
	{
		s = envp[i];
		ft_putstr_fd(s, 1); // change 1 to fd?
		ft_putstr_fd("\n", 1); // change 1 to fd?
		i++;
	}
	if (i == 0)
		ft_putstr_fd("(null)\n", 1); // change 1 to fd?
    return ;
}

// 9. function to export variable (export)


// 10. function for initial copy of char **envp into t_env_var *envars->our_envp
void	set_our_envp(char **envp, t_env_var *envars)
{
	int		i;
	int		size_of_array;

    i = 0;
	size_of_array = get_end_of_envp_list(envp);
	envars->our_envp = (char **)malloc((size_of_array + 1) * sizeof(char *));
	if (!envars->our_envp)
	{
		minishell_error("malloc fail make_our_env our_envp");
		exit (1);
	}
	while(envp[i] != NULL)
	{
		envars->our_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	envars->our_envp[i] = NULL;
    return ;
}
