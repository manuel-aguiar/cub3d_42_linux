/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_list_mpool_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:45:15 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:45:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "void_dl_list.h"

void	vdplist_del_head(t_vdplist *list, void (*del)(void *))
{
	t_vdpnode	*cur;

	if (!list || !(list->head))
		return ;
	cur = list->head;
	if (cur->next)
		cur->next->prev = NULL;
	else
		list->tail = NULL;
	list->head = cur->next;
	if (del)
		del(cur->data);
	mpool_dealloc(list->pool, cur);
	--(list->len);
}

void	vdplist_del_tail(t_vdplist *list, void (*del)(void *))
{
	t_vdpnode	*cur;

	if (!list || !(list->tail))
		return ;
	cur = list->tail;
	if (cur->prev)
		cur->prev->next = NULL;
	else
		list->head = NULL;
	list->tail = cur->prev;
	if (del)
		del(cur->data);
	mpool_dealloc(list->pool, cur);
	--(list->len);
}

void	vdplist_delall_content(t_vdplist *list, void (*del)(void *))
{
	t_vdpnode	*cur;

	if (!list || !del)
		return ;
	cur = list->head;
	while (cur)
	{
		del(cur->data);
		cur = cur->next;
	}
}

void	vdplist_destroy(t_vdplist **list, int keep_pool, void (*del)(void *))
{
	if (!list || !*list)
	{
		return ;
	}
	if (del)
	{
		vdplist_delall_content(*list, del);
	}
	if ((*list)->pool->pool_start && !keep_pool)
		mpool_destroy(&((*list)->pool));
	ft_free_set_null(list);
}
