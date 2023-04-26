#include <minishell.h>

void	sig_quit_handler(t_minishell *mini)
{
	ft_putstr_fd("exit", 2);
	ft_putchar_fd('\n', 2);
	free(mini->input);
	mini->input = NULL;
	// NEW_env_var_free_list(mini->env_list);
	// mini->env_list = NULL;
	exit(130); // change exit code
}

void	sig_int_handler(int sig)
{
	(void) sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	init_signals(void)
{
	signal(SIGINT, &sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
}