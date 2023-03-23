#include <minishell.h>
/*
int	main(int argc, char **argv, char **envp)
{
	(void) envp;
	if (argc != 2)
		return (EXIT_FAILURE);
	printf("|%s|\n", argv[1]);
	ft_str_reduce_char(argv[1], ' ');
	printf("|%s|\n", argv[1]);

	return (EXIT_SUCCESS);
}
*/

int	main(int argc, char **argv, char **envp)
 {
	t_minishell		mini;

 	(void)	argv;
	(void)	envp;
 	if (argc > 1)
		return (EXIT_FAILURE);
	if (init_shell(envp, &mini) == 1)
		return (1);
	while (1)
	{
		mini.input = readline(MARSH_PROMPT);
		if (mini.input == NULL || ft_strncmp(mini.input, "exit", 4) == 0)
			minishell_error("EXIT AT MINISHELL");
		complexer(&mini);
		here_doc_input(mini.cmd_list);
		list_cmd_free_list(mini.cmd_list); // remove once testing complexer is finished
 		free(mini.input);
 	}
 	return (EXIT_SUCCESS);
}
