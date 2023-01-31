/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 13:49:05 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:28:49 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Outputs the string ’s’ to the given file descriptor, followed by a newline.
*/

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	return ;
}
