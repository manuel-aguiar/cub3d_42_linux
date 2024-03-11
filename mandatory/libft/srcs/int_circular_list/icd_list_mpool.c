/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_list_mpool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:51:43 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:51:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_cd_list.h"

t_icpnode	*new_icpnode(int nbr, t_mpool *pool)
{
	t_icpnode	*new;

	if (!pool || !pool->pool_start)
		return (NULL);
	new = (t_icpnode *)mpool_alloc(pool);
	if (!new)
		return (NULL);
	new->data = nbr;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_icplist	*icplist_new(int elements, t_mpool *shared_pool)
{
	t_icplist	*list;
	t_mpool		*pool;

	list = malloc(sizeof(*list));
	if (!list)
		return (perror_msg_ptr("malloc", NULL));
	if (!shared_pool || shared_pool->block_size != sizeof(t_icpnode))
	{
		pool = mpool_create(sizeof(t_icpnode), elements);
		if (!pool)
		{
			free(list);
			return (NULL);
		}
	}
	else
		pool = shared_pool;
	list->pivot = NULL;
	list->pool = pool;
	list->len = 0;
	return (list);
}

void	icplist_in_head(t_icplist *list, int data)
{
	icplist_in_tail(list, data);
	list->pivot = list->pivot->prev;
}

void	icplist_in_tail(t_icplist *list, int data)
{
	t_icpnode	*new_node;

	if (!list)
		return ;
	new_node = new_icpnode(data, list->pool);
	if (!new_node)
		return ;
	if (list->pivot)
	{
		new_node->next = list->pivot;
		new_node->prev = list->pivot->prev;
		new_node->prev->next = new_node;
		new_node->next->prev = new_node;
	}
	else
	{
		new_node->next = new_node;
		new_node->prev = new_node;
		list->pivot = new_node;
	}
	++(list->len);
}
