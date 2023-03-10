#include <minishell.h>

// mini main by Maresiskoning

int	main(int argc, char **argv, char **envp)
{
	t_env_var_ll	*env_var_list = NULL;
	t_cmd		cmd;
	char		*input;
	const char	prompt[] = MARES_PROMPT;
	(void) argc; // to silence compiler
	(void) argv; // to silence compiler
	(void) envp; // to silence compiler

	if (init_shell(envp, &env_var_list) == 1)
		return (1);
	// print_linked_list(env_var_list);

	input = NULL;
	while (1)
	{
		input = readline(prompt);
		mini_parse_input(input, &cmd);
		if (builtin_check(cmd.simple_cmd) == true)
			builtin_execute(&cmd, &env_var_list);
	// 	free(cmd.simple_cmd);
	// 	free_double_array(cmd.args);
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