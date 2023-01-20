/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:04:48 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/01/20 14:32:17 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// readline main by Tentanus:
// int	main(int argc, char **argv, char **envp)
// {
	// char		*input;
	// const char	prompt[] = MARSH_PROMPT;
	// (void) argc; // to silence compiler
	// (void) argv; // to silence compiler
	// (void) envp; // to silence compiler
	// input = NULL;
	// while (1)
	// {
	// 	input = readline(prompt);
	// 	if (ft_strncmp(input, "exit", 4) == 0)
	// 		return (free(input), EXIT_SUCCESS);
	// 	printf("%s\n", input);
	// 	free(input);
	// }
	// return (0);
// }

// mini main by Maresiskoning
int	main(int argc, char **argv)
{
	t_cmd cmd;
	parse_input(argc, argv, &cmd);
	if (check_builtin(cmd.simple_cmd) == true)
		execute_builtin(&cmd);
	return (0);
}

// TO DO:
// mains verder samenvoegen:
// input parsen vanaf 'line' ipv argc, argv