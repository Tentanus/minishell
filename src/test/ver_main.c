#include <minishell.h>

// mini main by Maresiskoning

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env_var_ll	*env_var_list = NULL;
// 	t_cmd			cmd;
// 	char			*input;
// 	const char		prompt[] = MARES_PROMPT;
// 	(void) argc; // to silence compiler
// 	(void) argv; // to silence compiler
// 	(void) envp; // to silence compiler
// 	// t_cmd			*cmd_table = NULL; // ! for complex command and executor!

// 	if (init_shell(envp, &env_var_list) == 1)
// 		return (1);

// 	input = NULL;
// 	while (1)
// 	{
// 		input = readline(prompt);
// 		// mini_parse_input(input, &cmd);
// 		// complexer();
// 		// TODO: 2 lines hieronder uitcommenten executor() callen
// 		if (builtin_check(cmd.simple_cmd) == true)
// 			builtin_execute(&cmd, &env_var_list);
// 		// executor(&cmd_table, &env_var_list); // ! for complex command and executor!
// 		free(input);
// 	}
// 	// system("leaks -q martest");
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
 {
	t_minishell		mini;
	t_env_var_ll	*env_var_list = NULL;

 	(void)	argv;
	(void)	envp;
 	if (argc > 1)
		return (EXIT_FAILURE);
	if (init_shell(envp, &env_var_list) == 1)
		return (1);
	while (1)
	{
 		mini.input = readline(MARSH_PROMPT);
 		if (ft_strncmp(mini.input, "exit", 4) == 0)
			minishell_error("EXIT AT MINISHELL");
		complexer(&mini);
		// TO TEST:
		if (builtin_check(mini.cmd_list->args[0]) == true)
			builtin_execute(mini.cmd_list, &env_var_list);
 		free(mini.input);
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