/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:15:42 by manuel            #+#    #+#             */
/*   Updated: 2023/04/19 14:11:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*move;
	t_list	*delete;

	move = *lst;
	if (!lst || !*lst || !del)
		return ;
	while (move)
	{
		delete = move;
		move = move->next;
		ft_lstdelone(delete, del);
	}
	*lst = NULL;
}*/
