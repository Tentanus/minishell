#include <minishell.h>

void	sig_quit_handler(int sig)
{
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(sig, 2);
	ft_putchar_fd('\n', 2);
}

void	sig_int_handler()
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

void    init_signals()
{
    signal(SIGINT, &sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
}
