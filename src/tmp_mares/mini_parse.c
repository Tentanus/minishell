/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_parse.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 14:05:34 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/01/25 16:46:13 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_input(int argc, char **argv, t_cmd *cmd)
{
	cmd->simple_cmd = argv[1];
    // printf("%s\n", cmd->simple_cmd);
    cmd->amount_of_args = argc - 2; // ./martest en simple command eraf
    cmd->args = make_double_array(cmd->amount_of_args);
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

void	mini_parse_input(char *input, t_cmd *cmd)
{
	char **input_split = ft_split(input, ' ');
    cmd->simple_cmd = input_split[0];
    // printf("cmd->simple_cmd: %s\n", cmd->simple_cmd);
    cmd->amount_of_args = ft_word_counter(input, ' ');
    if (cmd->amount_of_args > 1)
    {
        // printf("cmd->amount_of_args: %i waarvan laatste = NULL\n", cmd->amount_of_args);
        cmd->args = make_double_array(cmd->amount_of_args);

        int i = 1;
        int j = 0;
        while (j < cmd->amount_of_args)
        {
            cmd->args[j] = input_split[i];
            j++;
            i++;
        }
        cmd->args[j] = NULL;

        // printing args to test:
        // i = 0;
        // while (i < cmd->amount_of_args)
        // {
        //     printf("cmd->args[%d] = %s\n", i, cmd->args[i]);
        //     i++;
        // }
    }
    return ;
}