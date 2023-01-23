#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	t_token	*top;

	(void) argc;
	(void) argv;
	(void) envp;

	if (argc != 2)
		return (EXIT_FAILURE);
	top = lexer(argv[1]);
	list_token_printf(top);
	return (0);
}
