#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token		*lst_token;

	(void) argv;
	(void) envp;
	if (argc > 1)
		return (EXIT_FAILURE);
	while (1)
	{
		input = readline(MARSH_PROMPT);
		if (ft_strncmp(input, "exit", 4) == 0)
			return (free(input), EXIT_SUCCESS);
		lst_token = lexer(input);
		list_token_print(lst_token);
		free(input);
	}
	return (EXIT_SUCCESS);
}
