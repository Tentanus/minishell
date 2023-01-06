#include <marshell.h>

int main(int argc, char **argv, char **envp)
{
	char	*input;
	(void) argc;
	(void) argv;
	(void) envp;
	input = NULL;

	while (1)
	{
		input = readline(prompt);
		
		free(input);
	}
}

/*
 * prompt: "\001\033[1;32m\002marsh-0.1> \001\033[0m\002"
 */
