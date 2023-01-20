/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_parse.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 14:05:34 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/01/20 11:04:53 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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