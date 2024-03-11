/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_list_mpool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:26:23 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/05/31 20:26:23 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_xor_list.h"

t_ixpnode	*xor_func(t_ixpnode *prev, t_ixpnode *next)
{
	return ((t_ixpnode *)((uintptr_t)prev ^ (uintptr_t)next));
}

static t_ixpnode	*new_ixpnode(int nbr, t_mpool *pool)
{
	t_ixpnode	*new;

	if (!pool || !pool->pool_start)
		return (NULL);
	new = (t_ixpnode *)mpool_alloc(pool);
	if (!new)
		return (NULL);
	new->data = nbr;
	new->xor_ptr = NULL;
	return (new);
}

t_ixplist	*ixplist_new(int elements, t_mpool *shared_pool)
{
	t_ixplist	*list;
	t_mpool		*pool;

	list = malloc(sizeof(*list));
	if (!list)
		return (perror_msg_ptr("malloc", NULL));
	if (!shared_pool || shared_pool->block_size != sizeof(t_ixpnode))
	{
		pool = mpool_create(sizeof(t_ixpnode), elements);
		if (!pool)
		{
			free(list);
			return (NULL);
		}
	}
	else
		pool = shared_pool;
	list->head = NULL;
	list->tail = NULL;
	list->pool = pool;
	list->len = 0;
	return (list);
}

void	ixplist_in_head(t_ixplist *list, int data)
{
	t_ixpnode	*new_node;

	if (!list)
		return ;
	new_node = new_ixpnode(data, list->pool);
	if (!new_node)
		return ;
	new_node->xor_ptr = list->head;
	if (list->head)
		list->head->xor_ptr = xor_func(new_node, list->head->xor_ptr);
	else
		list->tail = new_node;
	list->head = new_node;
	++(list->len);
}

void	ixplist_in_tail(t_ixplist *list, int data)
{
	t_ixpnode	*new_node;

	if (!list)
		return ;
	new_node = new_ixpnode(data, list->pool);
	if (!new_node)
		return ;
	new_node->xor_ptr = list->tail;
	if (list->tail)
		list->tail->xor_ptr = xor_func(list->tail->xor_ptr, new_node);
	else
		list->head = new_node;
	list->tail = new_node;
	++(list->len);
}
