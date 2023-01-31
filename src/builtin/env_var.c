#include <minishell.h>

/*
** This file contains functions to manage and change environment variables.
**
** function to print all envps (env builtin)
**
** function to add/set environment variable:
- equivalent of putenv() or setenv()
- create new string of format 'NAME=value'
- where to add variable,  at end?
**
** function to search for environment variable:
** - getenv om te checken of env var bestaat
** - daarna strncmp door envp's om goede env var te "pakken":
** if (strncmp(name, env_var, len(name)) == 0 && (env_var)[len] == '=') dan gevonden!
** - pointer naar juiste env var returnen?
**
** function to modify environment variable
**
** function to remove environment variable (unset builtin)
**
** function to export a variable (export builtin)
** 
**
** environment variables of 'NAME=value' format
** - getenv() gives the 'value'
** - looping through envp with envp[i] gives all environment variables.
*/


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


// void    set_env(char *name, char *value, int overwrite, char **envp)
void    set_env(char *name, char *value, char **envp)
{
	char *env_var;
    size_t env_var_size;
    
    printf("name = %s\n", name);
    printf("value = %s\n", value);
    printf("DUS WE ZIJN IN SET_ENV\n\n");

    // malloc for strlen(name) + strlen(value) + 2
    env_var_size = ft_strlen(name) + ft_strlen(value) + 2;
    env_var = malloc(env_var_size);
    if (!env_var)  // protect malloc!
    {
        minishell_error("set_env malloc");
		exit(1);
    }
    // make new env_var of format 'NAME=value'
    ft_strlcpy(env_var, name, env_var_size); // copy name to env_var
    printf("1. env var = %s\n", env_var);
    ft_strlcat(env_var, "=", env_var_size); // concatenate name and =
    printf("2. env var = %s\n", env_var);
    ft_strlcat(env_var, value, env_var_size); // concatenate name= and value
    printf("3. env var = %s\n\n", env_var);

	int var_index = search_for_env_index(name, envp);
	envp[var_index] = env_var;
    return ;
}

bool	env_var_exists(char *name)
{
	if (getenv(name) != NULL)
		return true;
	return false;
}
int		search_for_env_index(char *name, char **envp)
{
    int i;
    int len_name;

    printf("WE ZIJN IN SEARCH_FOR_ENV\n");

	i = 0;
	len_name = ft_strlen(name);
	if (env_var_exists(name) == true)
	{
		while(ft_strncmp(envp[i], name, len_name) != 0)
		{
			if (ft_strncmp(&envp[i][len_name], "=", 1) == 0)
				return (i);
			i++;
		}
		return (i);
	}
	else
	{
		int i = 0;
		while(envp[i])
			i++;
		return (i);
	}
}


// Code inspiration from chatGPT:
void	change_pwd_oldpwd(char **envp)
{
	char *new_working_dir;
    char *pwd = getenv("PWD");
    // char *pwd = "teeeest";
    char *oldpwd = getenv("OLDPWD");
    int len_pwd = strlen(pwd);
    int len_oldpwd = strlen(oldpwd);
    char *str_pwd = (char *)malloc(sizeof(char) * (len_pwd+4));
    char *str_oldpwd = (char *)malloc(sizeof(char) * (len_oldpwd+7));
    strcpy(str_oldpwd, "OLDPWD=");
    strcat(str_oldpwd, pwd);
    strcpy(str_pwd, "PWD=");
    strcat(str_pwd, new_working_dir);
    for (int i = 0; envp[i]; i++) {
        if (strncmp(envp[i], "OLDPWD=", 7) == 0) {
            envp[i] = str_oldpwd;
        }
        if (strncmp(envp[i], "PWD=", 4) == 0) {
            envp[i] = str_pwd;
        }
    }

	// print env's to check:
	print_env(envp);
}