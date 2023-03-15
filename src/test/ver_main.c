#include <minishell.h>

// mini main by Maresiskoning

int	main(int argc, char **argv, char **envp)
{
	t_env_var_ll	*env_var_list = NULL;
	t_cmd			cmd;
	char			*input;
	const char		prompt[] = MARES_PROMPT;
	(void) argc; // to silence compiler
	(void) argv; // to silence compiler
	(void) envp; // to silence compiler
	// t_cmd			*cmd_table = NULL; // ! for complex command and executor!

	if (init_shell(envp, &env_var_list) == 1)
		return (1);

	input = NULL;
	while (1)
	{
		input = readline(prompt);
		mini_parse_input(input, &cmd);
		// TODO: 2 lines hieronder uitcommenten executor() callen
		if (builtin_check(cmd.cmd) == true)
			builtin_execute(&cmd, &env_var_list);
		// executor(&cmd_table, &env_var_list); // ! for complex command and executor!
		free(input);
	}
	// system("leaks -q martest");
	return (0);
}

// !! TO DO:
// !!
// !! executer opzet maken (OP PAPIER MRAZ!!!)
// !!
// !! volgorde uitvoering commands bekijken en optimaliseren
// !! structuur functies optimaliseren en norm maken
// !! alle env functions goed checken en naar free-en kijken
// !!