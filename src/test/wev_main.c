#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	t_token	*top;

	(void) argc;
	(void) argv;
	(void) envp;

	top = NULL;
	if (argc != 2)
		return (EXIT_FAILURE);
	top = lexer(argv[1]);
	list_token_print(top);
	return (0);
}
