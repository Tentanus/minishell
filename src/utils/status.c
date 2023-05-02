#include <minishell.h>

void	status_update(unsigned int status)
{
	free(g_status.exit_str);
	g_status.exit_str = ft_itoa(status);
	// g_status.status = status;
}
