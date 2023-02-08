#include <minishell.h>

// mini main by Maresiskoning

int	main(int argc, char **argv, char **envp)
{
	t_env_var_old	our_env_var;
	t_cmd		cmd;
	char		*input;
	const char	prompt[] = MARES_PROMPT;
	(void) argc; // to silence compiler
	(void) argv; // to silence compiler
	(void) envp; // to silence compiler

	make_our_env(envp, &our_env_var);
	input = NULL;
	while (1)
	{
		input = readline(prompt);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free_double_array(our_env_var.our_envp);
			return (free(input), EXIT_SUCCESS);
		}
		mini_parse_input(input, &cmd);
		if (check_builtin(cmd.simple_cmd) == true)
			execute_builtin(&cmd, &our_env_var);
		free(cmd.simple_cmd);
		free_double_array(cmd.args);
		free(input);
	}
	system("leaks -q martest");
	free_double_array(our_env_var.our_envp);
	return (0);
}
