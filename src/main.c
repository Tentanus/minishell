/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:40:13 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/12 15:46:54 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*g_status;

void	init_mini(t_minishell *mini)
{
	mini->input = NULL;
	mini->token = NULL;
	mini->syntax = NULL;
	mini->cmd_list = NULL;
	mini->env_list = NULL;
	tcgetattr(STDIN_FILENO, &mini->saved_term);
	mini->saved_term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &mini->saved_term);
	g_status = ft_strdup("0");
	if (!g_status)
		mini_exit(error_print, 137, "unable to startup");
	return ;
}

void	f(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell		mini;

	(void) argv;
	atexit(f);
	if (argc > 1)
		mini_exit(error_print, 1, "too many arguments");
	init_mini(&mini);
	if (init_shell(envp, &mini) == 1)
		mini_exit(error_print, 1, "unable to startup");
	while (1)
	{
		sig_init();
		mini.input = readline(OCTO_PROMPT);
		if (mini.input == NULL)
			sig_quit_handler(&mini);
		if (ft_strncmp(mini.input, "", 1))
		{
			add_history(mini.input);
			complexer(&mini);
			executor(&mini);
		}
		free(mini.input);
		mini.input = NULL;
	}
}
