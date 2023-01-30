#include <minishell.h>

int	skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

void	ft_str_rmspace(char *inp)
{
	size_t	start_pos;
	size_t	current_pos;

	current_pos = skip_whitespace(inp);
	while (inp[current_pos])
	{
		if (!ft_strncmp(&inp[current_pos], "  ", 2))
		{
			start_pos = current_pos + 1;
			current_pos += skip_whitespace(&inp[current_pos]);
			ft_memmove(&inp[start_pos], &inp[current_pos], 
					(current_pos - start_pos));
		}
		else
			current_pos++;
	}
}
