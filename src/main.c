#include <minishell.h>

int	main(int argc, char **argv, char **envp)
 {
	t_minishell		mini;

 	(void)	argv;
 	if (argc > 1)
		return (EXIT_FAILURE);
	if (init_shell(envp, &mini) == 1)
		return (1);
	mini.cmd_list = NULL;
	mini.input= NULL;

	while (1)
	{
		init_signals(&mini);
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
			mini.cmd_list = NULL;
		}
		free(mini.input);
		mini.input = NULL;
	}
 	return (EXIT_SUCCESS);
}
