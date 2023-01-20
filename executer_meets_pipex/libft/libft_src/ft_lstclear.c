/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 16:29:09 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/04/20 12:28:17 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Deletes and frees the given element and every successor of that element,
** using the function ’del’ and free(). Finally, the pointer to the list must
** be set to NULL.
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*list;

	if (!lst)
		return ;
	list = *lst;
	while (list)
	{
		tmp = (list)->next;
		ft_lstdelone(list, del);
		list = tmp;
	}
	*lst = NULL;
}
