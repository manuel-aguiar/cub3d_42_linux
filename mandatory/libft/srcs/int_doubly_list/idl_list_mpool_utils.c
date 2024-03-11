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

#include "int_dl_list.h"

void	idplist_del_head(t_idplist *list)
{
	t_idpnode	*cur;

	if (!list || !(list->head))
		return ;
	cur = list->head;
	if (cur->next)
		cur->next->prev = NULL;
	else
		list->tail = NULL;
	list->head = cur->next;
	mpool_dealloc(list->pool, cur);
	--(list->len);
}

void	idplist_del_tail(t_idplist *list)
{
	t_idpnode	*cur;

	if (!list || !(list->tail))
		return ;
	cur = list->tail;
	if (cur->prev)
		cur->prev->next = NULL;
	else
		list->head = NULL;
	list->tail = cur->prev;
	mpool_dealloc(list->pool, cur);
	--(list->len);
}

void	idplist_head_print(t_idplist *list, void (*pnt)(int))
{
	t_idpnode	*cur;

	if (!list)
		return ;
	cur = list->head;
	while (cur)
	{
		pnt(cur->data);
		cur = cur->next;
	}
}

void	idplist_tail_print(t_idplist *list, void (*pnt)(int))
{
	t_idpnode	*cur;

	if (!list)
		return ;
	cur = list->tail;
	while (cur)
	{
		pnt(cur->data);
		cur = cur->prev;
	}
}

void	idplist_destroy(t_idplist **list, int keep_pool)
{
	if (!list || !*list)
		return ;
	if ((*list)->pool->pool_start && !keep_pool)
		mpool_destroy(&((*list)->pool));
	ft_free_set_null(list);
}
