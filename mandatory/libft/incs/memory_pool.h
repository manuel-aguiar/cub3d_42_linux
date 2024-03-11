/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_pool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:14:11 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 14:14:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
based on the work found on
https://arxiv.org/ftp/arxiv/papers/2210/2210.16471.pdf
whenever you allocate a block, and the block was used before, the index saved on
the block will be used to determine where the next free block is.
everytime a block is freed, it will be put at disposal for future allocations
by using a memory pool, one guarantees that the nodes will be closely alocated
as they are placed in the block, improving data locality while at the same time
avoiding multiple calls to malloc and null
*/

#ifndef MEMORY_POOL_H

# define MEMORY_POOL_H

# include <stdlib.h>
# include <stddef.h>

# include "error_handling.h"

# define UPSIZE 2

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;

typedef struct s_mpool
{
	t_uint			block_num;
	t_uint			block_size;
	t_uint			free_blocks;
	t_uint			used_blocks;
	t_uchar			*pool_start;
	t_uchar			*pool_end;
	t_uchar			*next_empty;
	struct s_mpool	*next_pool;
}	t_mpool;

t_mpool	*mpool_create(size_t block_size, t_uint block_num);
void	mpool_destroy(t_mpool **pool);
void	*mpool_alloc(t_mpool *pool);
void	mpool_dealloc(t_mpool *pool, void *p);

#endif
