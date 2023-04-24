#include <minishell.h>

// mini main by Maresiskoning

void test(void)
{
	system("leaks -q martest");
}

int	main(int argc, char **argv, char **envp)
 {
	t_minishell		mini;

	// atexit(test);
 	(void)	argv; // to silence compiler
	(void)	envp; // to silence compiler
 	if (argc > 1)
		return (EXIT_FAILURE);
	if (init_shell(envp, &mini) == 1)
		return (1);
	mini.cmd_list = NULL;
	mini.input= NULL;
	while (1)
	{
 		mini.input = readline(MARES_PROMPT);
		if (mini.input)
		{
			if (ft_strncmp(mini.input, "", 1))
				add_history(mini.input);
		}
		if (mini.input == NULL)
		{
			clear_history();
			printf("exit marshell\n");
			exit(EXIT_SUCCESS);
		}
		complexer(&mini);
		executor(&mini);
		list_cmd_free_list(mini.cmd_list); // remove once testing complexer is finished
		mini.cmd_list = NULL;
 		free(mini.input);
		mini.input = NULL;
 	}
	
 	return (EXIT_SUCCESS);
}
