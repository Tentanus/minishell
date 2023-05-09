/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 13:47:35 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/09 11:45:04 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_quit_handler(t_minishell *mini)
{
	ft_putendl_fd("exit", 2);
	free(mini->input);
	mini->input = NULL;
	exit(0);
}

void	sig_int_handler(int sig)
{
	(void) sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	status_update(1);
}

void	sig_init(void)
{
	signal(SIGINT, &sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
}
