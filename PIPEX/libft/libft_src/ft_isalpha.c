/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 17:36:27 by mverbrug      #+#    #+#                 */
/*   Updated: 2021/02/01 14:58:41 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** The isalpha() function tests for any character for which
** isupper() or islower() is true.
*/

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
