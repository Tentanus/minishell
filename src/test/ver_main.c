#include <minishell.h>

// mini main by Maresiskoning

int	main(int argc, char **argv, char **envp)
 {
	t_minishell		mini;

 	(void)	argv; // to silence compiler
	(void)	envp; // to silence compiler
 	if (argc > 1)
		return (EXIT_FAILURE);
	if (init_shell(envp, &mini) == 1)
		return (1);
	while (1)
	{
 		mini.input = readline(MARES_PROMPT);
		complexer(&mini);
		// TODO: 2 lines hieronder uitcommenten executor() callen
		// TO TEST:
		if (builtin_check(mini.cmd_list->args[0]) == true)
			builtin_execute(mini.cmd_list, &mini.env_list);
		// EXECUTOR:
		// executor();
 		free(mini.input);
 	}
	// system("leaks -q martest");
 	return (EXIT_SUCCESS);
}

// !! TO DO:
// !!
// !! executer opzet maken (OP PAPIER MRAZ!!!)
// !!
// !! volgorde uitvoering commands bekijken en optimaliseren
// !! structuur functies optimaliseren en norm maken
// !! alle env functions goed checken en naar free-en kijken
// !!