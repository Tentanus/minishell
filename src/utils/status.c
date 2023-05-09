/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   status.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 15:42:47 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/09 12:47:28 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	status_update(unsigned int status)
{
	free(g_status);
	g_status = ft_itoa(status);
	if (!g_status)
		mini_error(error_print, 1, "status not set. insufficient memory");
}
