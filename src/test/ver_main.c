#include <minishell.h>

// mini main by Maresiskoning

int	main(int argc, char **argv, char **envp)
{
	t_cmd		cmd;
	t_env		env;
	char		*input;
	const char	prompt[] = MARES_PROMPT;
	(void) argc; // to silence compiler
	(void) argv; // to silence compiler
	(void) envp; // to silence compiler

	input = NULL;
	while (1)
	{
		input = readline(prompt);
		if (ft_strncmp(input, "exit", 4) == 0)
			return (free(input), EXIT_SUCCESS);

		mini_parse_input(input, &cmd);
		if (check_builtin(cmd.simple_cmd) == true)
			execute_builtin(&cmd, &env, envp);
		free(input);
	}
	return (0);
}
