#include <minishell.h>

t_minishell	shell_init(char **envp)
{
	t_minishell	shell;

	shell.envp = envp;
	return (shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	t_token		*token;

	(void) argv;
	if (argc > 1)
		return (ERROR);
	shell = shell_init(envp);
	while (1)
	{
		shell.input = readline(MARSH_PROMPT);
		if (ft_strncmp(shell.input, "exit", 4) == 0)
			return (free(shell.input), SUCCESS);
		printf("%s\n", shell.input);
		token = lexer(shell.input);
//		lex_free(token);
		free(shell.input);
	}
	return (SUCCESS);
}
