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

#include "int_dl_list.h"

t_idpnode	*new_idpnode(int nbr, t_mpool *pool)
{
	t_idpnode	*new;

	if (!pool || !pool->pool_start)
		return (NULL);
	new = (t_idpnode *)mpool_alloc(pool);
	if (!new)
		return (NULL);
	new->data = nbr;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_idplist	*idplist_new(int elements, t_mpool *shared_pool)
{
	t_idplist	*list;
	t_mpool		*pool;

	list = malloc(sizeof(*list));
	if (!list)
		return (perror_msg_ptr("malloc", NULL));
	if (!shared_pool || shared_pool->block_size != sizeof(t_idpnode))
	{
		pool = mpool_create(sizeof(t_idpnode), elements);
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

void	idplist_in_head(t_idplist *list, int data)
{
	t_idpnode	*new_node;

	if (!list)
		return ;
	new_node = new_idpnode(data, list->pool);
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

void	idplist_in_tail(t_idplist *list, int data)
{
	t_idpnode	*new_node;

	if (!list)
		return ;
	new_node = new_idpnode(data, list->pool);
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
