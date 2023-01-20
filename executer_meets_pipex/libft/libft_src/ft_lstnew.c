/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 16:29:43 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:28:31 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Alocates (malloc) and returns a new element.
** The variable ’content’ is initialized with the value of the parameter
** ’content’. The variable ’next’ is initialized to NULL.
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	return (new);
}
