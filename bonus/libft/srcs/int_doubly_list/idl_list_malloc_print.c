/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idl_list_malloc_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:45:01 by marvin            #+#    #+#             */
/*   Updated: 2023/05/31 21:33:53 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_dl_list.h"

void	idmlist_head_print(t_idmlist *list, void (*pnt)(int))
{
	t_idmnode	*cur;

	if (!list)
		return ;
	cur = list->head;
	while (cur)
	{
		pnt(cur->data);
		cur = cur->next;
	}
}

void	idmlist_tail_print(t_idmlist *list, void (*pnt)(int))
{
	t_idmnode	*cur;

	if (!list)
		return ;
	cur = list->tail;
	while (cur)
	{
		pnt(cur->data);
		cur = cur->prev;
	}
}

int	idmlist_find(t_idmlist *list, int target)
{
	t_idmnode	*cur;

	if (!list || !(list->head))
		return (0);
	cur = list->head;
	while (cur)
	{
		if (cur->data == target)
			return (1);
		cur = cur->next;
	}
	return (0);
}
