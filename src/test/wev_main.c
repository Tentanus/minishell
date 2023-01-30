#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	int	cur_pos = 0;
	t_token	node;

	(void) envp;
	if (argc != 2)
		return (EXIT_FAILURE);

	get_token_info(argv[1], &cur_pos, &node);
	list_token_print(&node);
	return (EXIT_SUCCESS);
}
