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
bool	env_var_exists(char *name)
{
	if (getenv(name) != NULL)
		return true;
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
    // printf("1. env var = %s\n", env_var);
    ft_strlcat(env_var, "=", env_var_size); // concatenate name and =
    // printf("2. env var = %s\n", env_var);
    ft_strlcat(env_var, value, env_var_size); // concatenate name= and value
    // printf("3. env var = %s\n\n", env_var);
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
void    set_env(char *name, char *value, char **envp)
{
	char	*env_var = NULL;
	int		index = 0;

	env_var = make_env_var_format(name, value);
	index = search_for_env_index(name, envp);
	// if (env_var_exists(name) == true)
	// {
	// 	free(envp[index]);
	// 	envp[index] = NULL;
	// }
	// envp[index] = malloc(sizeof(ft_strlen(name) + ft_strlen(value) + 2));
	envp[index] = env_var;
	if (env_var_exists(name) == false)
	{
		// envp[index] = malloc(sizeof(ft_strlen(name) + ft_strlen(value) + 2));
		envp[index + 1] = NULL; // overwriting data we cannot access?
	}
	return ;
}

// 5. function to remove environment variable (unset builtin)

// 6. IS THIS REALLY NECESSARY?
int		get_end_of_envp_list(char **envp)
{
	int i;
	
	i = 0;
	while(envp[i])
		i++;
	return (i);
}

// 7.
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
    return ;
}

// 8. function to export variable (export)


// 9. ff proberen
char	**make_copy_env(char **envp)
{
    char	**our_envp;
	int		i;
	int		env_vars_at_start;
	int		envp_len;

    i = 0;
	env_vars_at_start = get_end_of_envp_list(envp);
	our_envp = (char **)malloc((env_vars_at_start + 1) * sizeof(char *));
	while(envp[i] != NULL)
	{
		envp_len = ft_strlen(envp[i]) + 1;
		our_envp[i] = (char *)malloc(envp_len * sizeof(char *));
		ft_strlcpy(our_envp[i], envp[i], envp_len);
		i++;
	}
	our_envp[i] = NULL;

	printf("our envp: \n");
	print_env(our_envp);
	// printf("\n\n");
    return (our_envp);
}