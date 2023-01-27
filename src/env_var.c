#include <minishell.h>

/*
** This file contains functions to manage and change environment variables.
**
** function to print all envps (for env)
** function to add/set environment variable (at end?)
** function to search environment variable (strcmp)
** function to modify environment variable
** function to remove environment variable
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