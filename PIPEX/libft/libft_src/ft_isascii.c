/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 18:45:13 by mverbrug      #+#    #+#                 */
/*   Updated: 2021/02/01 14:58:01 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** The isascii() function tests for an ASCII character,
** which is any character between 0 and octal 0177 inclusive.
*/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
