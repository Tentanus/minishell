#include <minishell.h>

int	main(int argc, char **argv, char **envp)
 {
	t_minishell		mini;

 	(void)	argv;
	(void)	envp;
 	if (argc > 1)
		return (EXIT_FAILURE);
	if (init_shell(envp, &mini) == 1)
		return (1);
	while (1)
	{
		mini.input = readline(MARSH_PROMPT);
		if (ft_strncmp(mini.input, "exit", 4) == 0)
			minishell_error("EXIT AT MINISHELL");
		complexer(&mini);
 		free(mini.input);
 	}
 	return (EXIT_SUCCESS);
}
