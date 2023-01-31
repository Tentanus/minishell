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
		// printf("envp[%d] = %s\n", i, envp[i]);
		// printf("%s\n", envp[i]);
		// printf("getenvp[%d] = %s\n", i, getenv(envp[i]));
		s = envp[i];
		ft_putstr_fd(s, 1); // change 1 to fd?
		ft_putstr_fd("\n", 1); // change 1 to fd?
		i++;
	}
    return ;
}

void    set_env(char *name, char *value, int overwrite, char **envp)
{
	char *env_var;
    
    // malloc for strlen(name) + strlen(value) + 2
    env_var = malloc(strlen(name) + strlen(value) + 2);
    // protect malloc!
    if (!env_var)
    {
        minishell_error("malloc set_env fail");
		exit(1);
        // throw error and exit/return
    }

    // make new env_var of format 'NAME=value'
    ft_strcpy(env_var, name); // copy name to env_var
    ft_strcat(env_var, "="); // concatenate name and =
    ft_strcat(env_var, value); // concatenate name= and value
    
    return ;
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