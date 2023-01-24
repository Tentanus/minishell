#include <minishell.h>

int	main(int argc, char **argv, char **envp)
 {
 	t_minishell	shell;
 	t_token		*lst_token;

 	(void) argv;
 	if (argc > 1)
		return (EXIT_FAILURE);
	while (1)
 		shell.input = readline(MARSH_PROMPT);
 		if (ft_strncmp(shell.input, "exit", 4) == 0)
 			return (free(shell.input), SUCCESS);
 		lst_token = lexer(shell.input);
 		list_token_print(lst_token);
 		free(shell.input);
 	}
 	return (EXIT_SUCCESS);