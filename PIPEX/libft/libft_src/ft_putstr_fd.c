/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 12:05:37 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:28:58 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

/*
** Outputs the string ’s’ to the given file descriptor.
*/

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (s)
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
	return ;
}
