/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vdlist_malloc_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:02:41 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/05/31 20:09:41 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "void_dl_list.h"

void	vdmlist_head_print(t_vdmlist *list, void (*pnt)(void *))
{
	t_vdmnode	*cur;

	if (!list)
		return ;
	cur = list->head;
	while (cur)
	{
		pnt(cur->data);
		cur = cur->next;
	}
}

void	vdmlist_tail_print(t_vdmlist *list, void (*pnt)(void *))
{
	t_vdmnode	*cur;

	if (!list)
		return ;
	cur = list->tail;
	while (cur)
	{
		pnt(cur->data);
		cur = cur->prev;
	}
}

int	vdmlist_find(t_vdmlist *list, void *data, int (*cmp)(void *, void *))
{
	t_vdmnode	*cur;

	if (!list || !(list->head) || !cmp)
		return (0);
	cur = list->head;
	while (cur)
	{
		if (!cmp(cur->data, data))
			return (1);
		cur = cur->next;
	}
	return (0);
}
