/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:14:07 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 14:14:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_pool.h"

t_mpool	*mpool_create(size_t block_size, t_uint block_num)
{
	t_mpool	*pool;

	pool = malloc(sizeof(*pool));
	if (!pool)
		return (perror_msg_ptr("malloc", NULL));
	pool->pool_start = malloc(block_size * block_num);
	if (!pool->pool_start)
	{
		perror_msg_ptr("malloc", NULL);
		free(pool);
		return (NULL);
	}
	pool->block_num = block_num;
	pool->block_size = block_size;
	pool->pool_end = pool->pool_start + pool->block_num * pool->block_size;
	pool->free_blocks = block_num;
	pool->next_empty = pool->pool_start;
	pool->used_blocks = 0;
	pool->next_pool = NULL;
	return (pool);
}

void	mpool_destroy(t_mpool **pool)
{
	t_mpool	*cur;
	t_mpool	*next;

	cur = *pool;
	while (cur)
	{
		free(cur->pool_start);
		cur->pool_start = NULL;
		next = cur->next_pool;
		free(cur);
		cur = next;
	}
	*pool = NULL;
}
