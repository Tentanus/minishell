#include <minishell.h>

// readline main by Tentanus:
// int	main(int argc, char **argv, char **envp)
// {
	// char		*input;
	// const char	prompt[] = MARSH_PROMPT;
	// (void) argc; // to silence compiler
	// (void) argv; // to silence compiler
	// (void) envp; // to silence compiler
	// input = NULL;
	// while (1)
	// {
	// 	input = readline(prompt);
	// 	if (ft_strncmp(input, "exit", 4) == 0)
	// 		return (free(input), EXIT_SUCCESS);
	// 	printf("%s\n", input);
	// 	free(input);
	// }
	// return (0);
// }

// mini main by Maresiskoning

int	main(int argc, char **argv)
{
	t_cmd		cmd;
	char		*input;
	const char	prompt[] = MARES_PROMPT;
	(void) argc; // to silence compiler
	(void) argv; // to silence compiler

	input = NULL;
	while (1)
	{
		input = readline(prompt);
		if (ft_strncmp(input, "exit", 4) == 0)
			return (free(input), EXIT_SUCCESS);

		mini_parse_input(input, &cmd);
		if (check_builtin(cmd.simple_cmd) == true)
			execute_builtin(&cmd);
		free(input);
	}
	return (0);
}
