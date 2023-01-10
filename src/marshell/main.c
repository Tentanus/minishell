#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	s_token	token;

	(void) argc;
	(void) argv;
	(void) envp;
	while (1)
	{
		input = readline(MARSH_PROMPT);
		if (ft_strncmp(input, "exit", 4) == 0)
			return (free(input), EXIT_SUCCESS);
		token = lexer(input);
		free(input);
	}
	return (0);
}
