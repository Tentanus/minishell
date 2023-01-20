#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	t_cmd cmd;
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
    parse_input(argc, argv, &cmd);
    if (check_builtin(cmd.simple_cmd) == true)
        execute_builtin(&cmd);
	return (0);
}
