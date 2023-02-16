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
	char		*input;
	t_minishell	mini;

 	(void)	argv;
	(void)	envp;
 	if (argc > 1)
		return (EXIT_FAILURE);
	while (1)
	{
 		mini.input = readline(MARSH_PROMPT);
 		if (ft_strncmp(input, "exit", 4) == 0)
			minishell_error("EXIT AT MINISHELL");
		printf("%s\n", input);
		parser(&mini);
 		free(input);
 	}
 	return (EXIT_SUCCESS);
}
