/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_list_mpool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:45:20 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:45:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "void_dl_list.h"

t_vdpnode	*new_vdpnode(void *data, t_mpool *pool)
{
	t_vdpnode	*new;

	if (!pool || !pool->pool_start)
		return (NULL);
	new = (t_vdpnode *)mpool_alloc(pool);
	if (!new)
		return (NULL);
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_vdplist	*vdplist_new(int elements, t_mpool *shared_pool)
{
	t_vdplist	*list;
	t_mpool		*pool;

	list = malloc(sizeof(*list));
	if (!list)
		return (perror_msg_ptr("malloc", NULL));
	if (!shared_pool || shared_pool->block_size != sizeof(t_vdpnode))
	{
		pool = mpool_create(sizeof(t_vdpnode), elements);
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

void	vdplist_in_head(t_vdplist *list, void *data)
{
	t_vdpnode	*new_node;

	if (!list)
		return ;
	new_node = new_vdpnode(data, list->pool);
	if (!new_node)
		return ;
	if (list->head)
	{
		new_node->next = list->head;
		list->head->prev = new_node;
	}
	else
		list->tail = new_node;
	list->head = new_node;
	++(list->len);
}

void	vdplist_in_tail(t_vdplist *list, void *data)
{
	t_vdpnode	*new_node;

	if (!list)
		return ;
	new_node = new_vdpnode(data, list->pool);
	if (!new_node)
		return ;
	if (list->tail)
	{
		new_node->prev = list->tail;
		list->tail->next = new_node;
	}
	else
		list->head = new_node;
	list->tail = new_node;
	++(list->len);
}
