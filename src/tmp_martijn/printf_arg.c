/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_arg.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 15:32:09 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/08 15:34:57 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("arg[%d]:\t|%s|\n", i, argv[i]);
		i++;
	}
	return (1);
}
