#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/new/assert.h>
#include "include/minishell.h"

static void redirect_all_std(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

static void	setup(void)
{
	redirect_all_std();
}

Test(misc, failing, .init=setup)
{
    char		*input = "echo Hello, World!";
    t_cmd		cmd;

    mini_parse_input(input, &cmd);
    execute_echo(&cmd, 1);

    // ft_putstr_fd("Hello, World!", 1);

    cr_assert_stdout_eq_str("Hello, World!");
}