#include <minishell.h>

// mini main by Maresiskoning

int	main(int argc, char **argv, char **envp)
{
	// t_env_var	envars;
	t_env_var_ll	envars;
	t_cmd		cmd;
	char		*input;
	const char	prompt[] = MARES_PROMPT;
	(void) argc; // to silence compiler
	(void) argv; // to silence compiler
	(void) envp; // to silence compiler

	// set_our_envp(envp, &envars);
	if (init_env_var(envp) == 1)
		return (1);
	print_linked_list(envars);

	input = NULL;
	while (1)
	{
		input = readline(prompt);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			// free_double_array(envars.our_envp);
			return (free(input), EXIT_SUCCESS);
		}
		mini_parse_input(input, &cmd);
		if (check_builtin(cmd.simple_cmd) == true)
			execute_builtin(&cmd, &envars);
		free(cmd.simple_cmd);
		free_double_array(cmd.args);
		free(input);
	}
	// system("leaks -q martest");
	// free_double_array(envars.our_envp);
	return (0);
}

// !! TO DO:
// !!
// !! export function maken (#9)
// !! volgorde uitvoering commands bekijken en optimaliseren
// !! structuur functies optimaliseren en norm maken
// !! alle env functions goed checken en naar free-en kijken
// !!
// !! exit builtin maken (denk aan goed free-en)
// !! executer opzet maken (OP PAPIER MRAZ!!!)

// ?? init shell function maken:
// ! The parent shell copies the exported variables and their values when creating the child shell!