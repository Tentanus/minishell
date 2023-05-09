/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:30:04 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/05/09 10:30:05 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** our own env function: it prints all environment variables (env builtin)
*/

int	builtin_env(t_env_var_ll *env_var_list)
{
	while (env_var_list != NULL)
	{
		if (env_var_list->has_value == true)
		{
			ft_putstr_fd(env_var_list->name, 2);
			ft_putstr_fd("=", 2);
			ft_putendl_fd(env_var_list->value, 2);
		}
		env_var_list = env_var_list->next;
	}
	return (SUCCESS);
}
