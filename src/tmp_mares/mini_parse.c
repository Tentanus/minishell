/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_parse.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 14:05:34 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/02/08 14:19:27 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_parse_input(char *input, t_cmd *cmd)
{
	char **input_split = ft_split(input, ' ');
    cmd->simple_cmd = malloc(ft_strlen(input_split[0]) * sizeof(char));
    ft_strlcpy(cmd->simple_cmd, input_split[0], ft_strlen(input_split[0]) + 1);
    cmd->amount_of_args = ft_word_counter(input, ' ');
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
    // free_double_array(input_split);
    return ;
}