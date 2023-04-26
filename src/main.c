#include <minishell.h>

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
		minishell_error("INIT g_status");
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
	init_mini(&mini);
 	if (argc > 1)
		return (EXIT_FAILURE); // error message saying user should run "./minishell" without other arguments
	if (init_shell(envp, &mini) == 1)
		return (1);
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
	// env_var_free_list(mini.env_list);
	// mini.env_list = NULL;
	// free(&mini);
 	return (EXIT_SUCCESS);
}
