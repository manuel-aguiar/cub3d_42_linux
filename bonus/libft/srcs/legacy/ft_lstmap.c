/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:34:54 by manuel            #+#    #+#             */
/*   Updated: 2023/04/19 14:11:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "libft.h"

static t_list	*ft_lstclear_nullret(t_list **lst, void (*del)(void*))
{
	t_list	*move;
	t_list	*delete;

	move = *lst;
	if (!lst)
		return (NULL);
	while (move)
	{
		delete = move;
		move = move->next;
		del(delete);
		delete = NULL;
	}
	*lst = NULL;
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*save_new;

	if (!lst)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (ft_lstclear_nullret(&lst, del));
	save_new = new;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstnew(f(lst->content));
		if (!new->next)
		{
			ft_lstclear(&save_new, del);
			return (ft_lstclear_nullret(&lst, del));
		}
		new = new->next;
		lst = lst->next;
	}
	return (save_new);
}*/
