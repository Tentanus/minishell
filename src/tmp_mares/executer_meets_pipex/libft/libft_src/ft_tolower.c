/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:42:51 by mverbrug      #+#    #+#                 */
/*   Updated: 2021/02/09 13:11:54 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** The tolower() function converts an upper-case letter to the
** corresponding lower-case letter.
*/

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}
