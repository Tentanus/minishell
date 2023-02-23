#include <minishell.h>

// mini main by Maresiskoning

int	main(int argc, char **argv, char **envp)
{
	// t_env_var	envars; // OLD
	t_env_var_ll	*env_var_list = NULL;
	t_cmd		cmd;
	char		*input;
	const char	prompt[] = MARES_PROMPT;
	(void) argc; // to silence compiler
	(void) argv; // to silence compiler
	(void) envp; // to silence compiler

	// set_our_envp(envp, &envars); OLD
	if (init_env_var(envp, &env_var_list) == 1)
		return (1);
	// print_linked_list(env_var_list);

	input = NULL;
	while (1)
	{
		input = readline(prompt);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			// free_double_array(envars.our_envp); OLD
			return (free(input), EXIT_SUCCESS);
		}
		mini_parse_input(input, &cmd);
		if (check_builtin(cmd.simple_cmd) == true)
			execute_builtin(&cmd, &env_var_list);
		printf("check envar_exists USER: = %s\n", env_var_exists("USER", env_var_list) ? "true" : "false");
		printf("check envar_exists RANDOM: = %s\n", env_var_exists("RANDOM", env_var_list) ? "true" : "false");

	// 		execute_builtin(&cmd, &envars); OLD

	// 	free(cmd.simple_cmd);
	// 	free_double_array(cmd.args);
		free(input);
	}
	// system("leaks -q martest");
	// free_double_array(envars.our_envp); OLD
	return (0);
}

// !! TO DO:
// !!
// !! environment variables als linked list opslaan
// !! - struct maken
// !! - linked list aanmaken
// !! bestaande env function herschrijven naar linked list structuur
// !! export function maken
// !! exit builtin maken (denk aan goed free-en)
// !!
// !! volgorde uitvoering commands bekijken en optimaliseren
// !! structuur functies optimaliseren en norm maken
// !! alle env functions goed checken en naar free-en kijken
// !!
// !! executer opzet maken (OP PAPIER MRAZ!!!)

// ?? init shell function maken:
// ! The parent shell copies the exported variables and their values when creating the child shell!