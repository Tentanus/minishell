/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 18:46:11 by mverbrug      #+#    #+#                 */
/*   Updated: 2021/02/09 13:12:01 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** The toupper() function converts a lower-case letter to the
** corresponding upper-case letter.
*/

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}
