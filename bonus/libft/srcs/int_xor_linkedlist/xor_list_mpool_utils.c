/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_list_mpool_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:26:13 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/05/31 20:26:13 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_xor_list.h"
#include <stdio.h>

t_ixpnode	*xor_func(t_ixpnode *prev, t_ixpnode *next);

void	ixplist_del_head(t_ixplist *list)
{
	t_ixpnode	*cur;
	t_ixpnode	*next;

	if (!list || !(list->head))
		return ;
	cur = list->head;
	next = xor_func(cur->xor_ptr, NULL);
	if (next)
		next->xor_ptr = xor_func(cur, next->xor_ptr);
	else
		list->tail = NULL;
	list->head = next;
	mpool_dealloc(list->pool, cur);
	--(list->len);
}

void	ixplist_del_tail(t_ixplist *list)
{
	t_ixpnode	*cur;
	t_ixpnode	*prev;

	if (!list || !(list->tail))
		return ;
	cur = list->tail;
	prev = xor_func(cur->xor_ptr, NULL);
	if (prev)
		prev->xor_ptr = xor_func(prev->xor_ptr, cur);
	else
		list->head = NULL;
	list->tail = prev;
	mpool_dealloc(list->pool, cur);
	--(list->len);
}

void	ixplist_head_print(t_ixplist *list, void (*pnt)(int))
{
	t_ixpnode	*cur;
	t_ixpnode	*prev;
	t_ixpnode	*next;

	if (!list)
		return ;
	cur = list->head;
	prev = NULL;
	while (cur)
	{
		pnt(cur->data);
		next = xor_func(prev, cur->xor_ptr);
		prev = cur;
		cur = next;
	}
}

void	ixplist_tail_print(t_ixplist *list, void (*pnt)(int))
{
	t_ixpnode	*cur;
	t_ixpnode	*prev;
	t_ixpnode	*next;

	if (!list)
		return ;
	cur = list->tail;
	next = NULL;
	while (cur)
	{
		pnt(cur->data);
		prev = xor_func(next, cur->xor_ptr);
		next = cur;
		cur = prev;
	}
}

void	ixplist_destroy(t_ixplist **list, int keep_pool)
{
	if (!list || !*list)
		return ;
	if ((*list)->pool->pool_start && !keep_pool)
		mpool_destroy(&((*list)->pool));
	ft_free_set_null(list);
}
