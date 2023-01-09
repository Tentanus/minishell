#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	const char	prompt[] = MARSH_PROMPT;

	(void) argc;
	(void) argv;
	(void) envp;
	input = NULL;
	while (1)
	{
		input = readline(prompt);
		if (ft_strncmp(input, "exit", 4) == 0)
			return (free(input), EXIT_SUCCESS);
		printf("%s\n", input);
		free(input);
	}
	return (0);
}
