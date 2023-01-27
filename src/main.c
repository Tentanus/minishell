#include <minishell.h>

int	main(int argc, char **argv, char **envp)
 {
	char		*input;

 	(void)	argv;
	(void)	envp;
 	if (argc > 1)
		return (EXIT_FAILURE);
	while (1)
	{
 		input = readline(MARSH_PROMPT);
 		if (ft_strncmp(input, "exit", 4) == 0)
			minishell_error("EXIT AT MINISHELL");
		printf("%s\n", input);
 		free(input);
 	}
 	return (EXIT_SUCCESS);
}