#include <minishell.h>

// mini main by Maresiskoning

void test(void)
{
	system("leaks -q martest");
}

int	main(int argc, char **argv, char **envp)
 {
	t_minishell		mini;

	// atexit(test);
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
		// EXECUTOR:
		executor(&mini);
 		free(mini.input);
		mini.input = NULL;
 	}
	
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