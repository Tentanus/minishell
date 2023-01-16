/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 18:45:34 by mverbrug      #+#    #+#                 */
/*   Updated: 2021/01/29 16:50:08 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** The isdigit() function tests for a decimal digit character.
*/

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}
