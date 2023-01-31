/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 16:29:54 by mverbrug      #+#    #+#                 */
/*   Updated: 2021/02/01 14:58:13 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** The isprint() function tests for any printing character,
** including space (` ').
*/

int	ft_isprint(int c)
{
	return (c >= 32 && c < 127);
}
