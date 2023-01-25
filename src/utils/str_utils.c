#include <minishell.h>

int	skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

