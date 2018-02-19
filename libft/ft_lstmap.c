/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:11:11 by yabdulha          #+#    #+#             */
/*   Updated: 2017/11/29 13:12:35 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlist;
	t_list	*head;

	if (!(newlist = (t_list*)malloc(sizeof(*newlist))))
		return (NULL);
	newlist = f(lst);
	head = newlist;
	while (lst->next != NULL)
	{
		lst = lst->next;
		if (!(newlist->next = (t_list*)malloc(sizeof(*newlist))))
			return (NULL);
		newlist->next = f(lst);
		newlist = newlist->next;
	}
	return (head);
}
