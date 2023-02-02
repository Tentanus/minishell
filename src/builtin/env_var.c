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
			return (i);
		i++;
	}
	return (-1);
}

// 4. function to set environment variable:
// equivalent of putenv() or setenv()
void    set_env(char *name, char *value, char **envp)
{
	char	*env_var = NULL;
	int		index = 0;

	env_var = make_env_var_format(name, value);
	// printf("env_var in set_env = %s\n", env_var);
	if (env_var_exists(name) == true)
	{
		printf("env_var %s does exist\n", name);
		index = search_for_env_index(name, envp);
		// free(envp[index]); // ????
	}
	else
	{
		printf("env_var %s does NOT YET exist\n", name);
		index = get_end_of_envp_list(envp) + 1;
	}
	envp[index] = env_var; // op de een of andere manier doet ie dit niet??
	printf("envp[index] op eind van set_env = %s\n\n", envp[index]);

	printf("envp at the end of set_env:\n\n");
	print_env(envp); // envp wordt niet geupdate??
	return ;
}

// 5. function to remove environment variable (unset builtin)

// 6.
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
	while(envp[i])
	{
		s = envp[i];
		ft_putstr_fd(s, 1); // change 1 to fd?
		ft_putstr_fd("\n", 1); // change 1 to fd?
		i++;
	}
    return ;
}

// 8. function to export variable (export)
