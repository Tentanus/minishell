#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell		mini;

	(void)	argv;
	(void)	envp;
	if (argc > 1)
		return (EXIT_FAILURE);
	if (init_shell(envp, &mini) == 1)
		return (1);
	mini.cmd_list = NULL;
	mini.input= NULL;
	while (1)
	{
		mini.input = readline(MARSH_PROMPT);
		if (mini.input)
		{
			if (ft_strncmp(mini.input, "", 1))
				add_history(mini.input);
		}
		if (mini.input == NULL || ft_strncmp(mini.input, "exit", 4) == 0)
		{
			clear_history();
			printf("exiting marshell\n");
			exit(EXIT_SUCCESS);
		}
		complexer(&mini);
//		list_cmd_print(mini.cmd_list);
		executor(&mini);
		list_cmd_free_list(mini.cmd_list); // remove once testing complexer is finished
		mini.cmd_list = NULL;
		free(mini.input);
		mini.input = NULL;
	}
	return (EXIT_SUCCESS);
}
