#include <minishell.h>

t_status	g_status;

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
	g_status.exit_str = ft_strdup("0");
	if (!g_status.exit_str)
		mini_exit_test(error_print, 137, "out of memory");
	return ;
}

// void test(void)
// {
// 	system("leaks -q marshell");
// }

int	main(int argc, char **argv, char **envp)
{
	t_minishell		mini;

	// atexit(test); // ! remove after testing!
	(void)	argv;
	if (argc > 1)
		mini_exit_test(error_print, 1, "too many arguments");
	init_mini(&mini);
	if (init_shell(envp, &mini) == 1)
		mini_exit_test(error_print, 1, "unable to startup");
	while (1)
	{
		init_signals();
		mini.input = readline(OCTO_PROMPT);
		if (mini.input == NULL)
			sig_quit_handler(&mini);
		if (ft_strncmp(mini.input, "", 1))
		{
			add_history(mini.input);
			complexer(&mini);
			executor(&mini);
			list_cmd_free_list(mini.cmd_list);
			mini.cmd_list = NULL;
		}
		free(mini.input);
		mini.input = NULL;
	}
	exit(EXIT_SUCCESS);
}
