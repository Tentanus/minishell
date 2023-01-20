/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 14:05:34 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/01/20 10:54:00 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	cmd1(t_args *arg, char **argv, char *path_complete)
{
	arg->cmd1_split = get_cmd(argv[2]);
	if (!arg->cmd1_split)
		exit(127);
	arg->path_to_cmd1 = check_cmd(arg->cmd1_split, path_complete);
	if (!arg->path_to_cmd1)
		exit(127);
}

void	cmd2(t_args *arg, char **argv, char *path_complete)
{
	arg->cmd2_split = get_cmd(argv[3]);
	if (!arg->cmd2_split)
		exit(127);
	arg->path_to_cmd2 = check_cmd(arg->cmd2_split, path_complete);
	if (!arg->path_to_cmd2)
		exit(127);
}

char	**get_cmd(char *input)
{
	int		word_count;
	char	**input_split;

	input_split = ft_split(input, ' ');
	if (!input_split)
		exit(127);
	word_count = ft_word_counter(input, ' ');
	if (str_is_space(input) != 0)
		input_split = check_sed(input_split, word_count);
	return (input_split);
}

/*
	parse_input calls to find full path in envp,
	fills struct with files and
	checks if cmds are not empty or existing of only whitespaces.
	If not, cmds are parsed.
*/

// void	parse_input(t_args *arg, char **argv, char **envp)
// {
// 	char	*path_complete;

// 	path_complete = find_path_complete(envp);
// 	if (!path_complete)
// 		exit_message("No such file or directory", 127);
// 	arg->infile = argv[1];
// 	arg->outfile = argv[4];
// 	if (checks(argv) != 1 && checks(argv) != 2)
// 		cmd1(arg, argv, path_complete);
// 	if (checks(argv) != 3 && checks(argv) != 4)
// 		cmd2(arg, argv, path_complete);
// 	free(path_complete);
// }

// char	**ft_make_array(int word_count)
// {
// 	char	**result;

// 	result = malloc((word_count + 1) * sizeof(char *));
// 	if (!result)
// 		return (NULL);
// 	return (result);
// }

void	parse_input(int argc, char **argv, t_cmd *cmd)
{
	cmd->simple_cmd = argv[1];
    // printf("%s\n", cmd->simple_cmd);
    cmd->amount_of_args = argc - 2;
    cmd->args = ft_make_array(cmd->amount_of_args);
	int i = 2;
    int j = 0;
    while (i < argc)
    {
        cmd->args[j] = argv[i];
        j++;
        i++;
    }
    cmd->args[j] = NULL;
    return ;
}