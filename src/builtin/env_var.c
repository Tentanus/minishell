#include <minishell.h>

/*
** This file contains functions to manage and change environment variables.
**
** 1. function to check if environment variable already exists:
** getenv om te checken of env var bestaat
**
** 2. function to make 'NAME=value' format string
**
** 3. function to get index of existing env_var
** loop door envp's
** strncmp envp met NAME:
** if (strncmp(name, env_var, len(name)) == 0 && (env_var)[len(name)] == '=') dan gevonden!
**
** 4. function to set environment variable:
** equivalent of putenv() or setenv()
**
** 5. function to remove environment variable (unset builtin)
**
** 6. function to get index of end of existing env_var list
**
** 7. function to print all envps (env builtin)
**
** 8. function to export a variable (export builtin)
**
*/

// 1.
bool	get_env_var_exists(char *name)
{
	if (getenv(name) != NULL)
		return true;
	return false;
}

bool	env_var_exists(char *name, char **env_vars)
{
	int i;
    int len_name;

	i = 0;
	len_name = ft_strlen(name);
	while (env_vars[i] != NULL)
	{
		if (ft_strncmp(env_vars[i], name, len_name) == 0 &&
				ft_strncmp(&env_vars[i][len_name], "=", 1) == 0)
			return true;
		i++;
	}
	return false;
}

// 2.
char	*make_env_var_format(char *name, char *value)
{
	char *env_var;
    size_t env_var_size;

    // malloc for strlen(name) + strlen(value) + 2
    env_var_size = ft_strlen(name) + ft_strlen(value) + 2;
    env_var = malloc(env_var_size);
    if (!env_var)  // protect malloc!
    {
        minishell_error("make_env_var_format malloc");
		exit(1);
    }
    // make new env_var of format 'NAME=value'
    ft_strlcpy(env_var, name, env_var_size); // copy name to env_var
    ft_strlcat(env_var, "=", env_var_size); // concatenate name and =
    ft_strlcat(env_var, value, env_var_size); // concatenate name= and value
	return (env_var);
}

// 3.
int		search_for_env_index(char *name, char **envp)
{
    int i;
    int len_name;

	i = 0;
	len_name = ft_strlen(name);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], name, len_name) == 0 &&
				ft_strncmp(&envp[i][len_name], "=", 1) == 0)
			break;
		i++;
	}
	return (i);
}

// 4. function to set environment variable:
// equivalent of putenv() or setenv()
void    set_env(char *name, char *value, t_env_var *our_env_var)
{
	char	*env_var = NULL;
	int		index;
	int		len_env_var;

	index  = 0;
	env_var = make_env_var_format(name, value);
	len_env_var = ft_strlen(env_var) + 1;
	index = search_for_env_index(name, our_env_var->our_envp);
	// if (env_var_exists(name, our_env_var->our_envp) == true)
	// {
	// 	free(our_env_var->our_envp[index]); // verdwijnt dan deze hele pointer?
	// }
	if (env_var_exists(name, our_env_var->our_envp) == false)
	{
		printf("we zijn hier met name = %s\n", name);
		our_env_var->our_envp[index] = (char *)malloc(len_env_var * sizeof(char *));
		our_env_var->our_envp[index + 1] = NULL;
	}
	our_env_var->our_envp[index] = env_var; // of ft_strlcpy(our_envp[i], envp[i], envp_len);
	printf("is het gelukt? our_env_var->our_envp[index] = %s\n", our_env_var->our_envp[index]);
	return ;
}

// 5. function to remove environment variable (unset builtin)

// 6. IS THIS REALLY NECESSARY?
int		get_end_of_envp_list(char **env_vars)
{
	int i;
	
	i = 0;
	while(env_vars[i])
		i++;
	return (i);
}

// 7.
void    print_env(char **env_vars)
{
    int i;
	char *s;
    
    i = 0;
	while(env_vars[i] != NULL)
	{
		s = env_vars[i];
		ft_putstr_fd(s, 1); // change 1 to fd?
		ft_putstr_fd("\n", 1); // change 1 to fd?
		i++;
	}
    return ;
}

// 8. function to export variable (export)


// 9. ff proberen
void	make_our_env(char **envp, t_env_var *our_env_var)
{
	int		i;
	int		env_vars_at_start;
	int		envp_len;

    i = 0;
	env_vars_at_start = get_end_of_envp_list(envp);
	our_env_var->our_envp = (char **)malloc((env_vars_at_start + 1) * sizeof(char *));
	if (!our_env_var->our_envp)
	{
		minishell_error("malloc fail make_our_env our_envp");
		exit (1);
	}
	while(envp[i] != NULL)
	{
		envp_len = ft_strlen(envp[i]) + 1;
		our_env_var->our_envp[i] = (char *)malloc(envp_len * sizeof(char *));
		if (!our_env_var->our_envp[i])
		{
			minishell_error("malloc fail make_our_env our_envp[i]");
			exit (1);
		}
		ft_strlcpy(our_env_var->our_envp[i], envp[i], envp_len);
		i++;
	}
	our_env_var->our_envp[i] = NULL;

	printf("\n our envp at end of make_our_envp: \n");
	print_env(our_env_var->our_envp);
	printf("\n waaah \n");
    return ;
}


char	*get_env(char *name, t_env_var *our_env_var)
{
	int		index;
	int		len_name;

	index = 0;
	len_name = ft_strlen(name);
	if (env_var_exists(name, our_env_var->our_envp) == true)
	{
		index = search_for_env_index(name, our_env_var->our_envp);
		return (&our_env_var->our_envp[index][len_name + 1]);
	}
	else
		return (NULL);
}