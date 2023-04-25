#include <minishell.h>

void	init_start(t_minishell *mini)
{
	tcgetattr(STDIN_FILENO, &mini->saved_term);
	mini->saved_term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &mini->saved_term);
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
		return (EXIT_FAILURE);
	if (init_shell(envp, &mini) == 1)
		return (1);
	mini.cmd_list = NULL;
	mini.input = NULL;

	init_start(&mini);
	while (1)
	{
		init_signals();
		mini.input = readline(OCTO_PROMPT);
		// printf("|%s|\n", mini.input);
		if (mini.input == NULL)
			sig_quit_handler(&mini);
		if (ft_strncmp(mini.input, "", 1))
		{
			add_history(mini.input);
			complexer(&mini);
			executor(&mini);
			list_cmd_free_list(mini.cmd_list);
			// env_var_free_list(&mini.env_list);
			NEW_env_var_free_list(mini.env_list);
			mini.cmd_list = NULL;
		}
		free(mini.input);
		mini.input = NULL;
	}
	// free(&mini);
 	return (EXIT_SUCCESS);
}
