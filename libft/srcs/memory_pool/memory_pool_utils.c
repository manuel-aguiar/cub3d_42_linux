/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_pool_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:35:02 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 14:35:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_pool.h"

/*
POTENCIAL PROBLEMA NAS LINHAS 36 e 42, pool->used_blocks, pool->free_blocks
*/
static t_uchar	*index_addr(const t_mpool *pool, t_uint i)
{
	return (pool->pool_start + (i * pool->block_size));
}

static t_uint	addr_index(const t_mpool *pool, const t_uchar *p)
{
	return (((t_uint)(p - pool->pool_start)) / pool->block_size);
}

void	*mpool_alloc(t_mpool *pool)
{
	t_uint	*p;
	void	*ret;

	if (pool->used_blocks < pool->block_num)
	{
		p = (t_uint *)index_addr(pool, pool->used_blocks);
		*p = pool->used_blocks++ + 1;
	}
	ret = NULL;
	if (pool->free_blocks > 0)
	{
		ret = (void *)pool->next_empty;
		if (--pool->free_blocks != 0)
			pool->next_empty = index_addr(pool, *((t_uint *)pool->next_empty));
		else
			pool->next_empty = NULL;
	}
	else
	{
		if (!pool->next_pool)
			pool->next_pool = \
			mpool_create(pool->block_size, pool->block_num * UPSIZE);
		return (mpool_alloc(pool->next_pool));
	}
	return (ret);
}

void	mpool_dealloc(t_mpool *pool, void *to_free)
{
	if (!pool || !to_free)
		return ;
	if ((t_uchar *)to_free >= pool->pool_start \
	&& (t_uchar *)to_free < pool->pool_end)
	{
		if (pool->next_empty != NULL)
		{
			(*(t_uint *)to_free) = addr_index(pool, pool->next_empty);
			pool->next_empty = (t_uchar *)to_free;
		}
		else
		{
			*((t_uint *)to_free) = pool->block_num;
			pool->next_empty = (t_uchar *)to_free;
		}
		++pool->free_blocks;
	}
	else
		mpool_dealloc(pool->next_pool, to_free);
}
