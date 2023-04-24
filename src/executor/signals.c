#include <minishell.h>

void	sig_quit_handler(t_minishell *mini)
{
	ft_putstr_fd("exit", 2);
	ft_putchar_fd('\n', 2);
	free(mini->input);
	mini->input = NULL;
	exit(130); // change exit code
}

void	sig_int_handler()
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sig_int_here_handler()
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void    init_signals()
{
	signal(SIGINT, &sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
}

