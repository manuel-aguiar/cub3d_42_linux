/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vdlist_mpool_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:59:05 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/05/31 19:59:41 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "void_dl_list.h"

void	vdplist_head_print(t_vdplist *list, void (*pnt)(void *))
{
	t_vdpnode	*cur;

	if (!list)
		return ;
	cur = list->head;
	while (cur)
	{
		pnt(cur->data);
		cur = cur->next;
	}
}

void	vdplist_tail_print(t_vdplist *list, void (*pnt)(void *))
{
	t_vdpnode	*cur;

	if (!list)
		return ;
	cur = list->tail;
	while (cur)
	{
		pnt(cur->data);
		cur = cur->prev;
	}
}
