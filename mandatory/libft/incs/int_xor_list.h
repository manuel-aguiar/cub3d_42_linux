/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_xor_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:45:46 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 14:45:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_XOR_LIST_H

# define INT_XOR_LIST_H

# include <stdlib.h>
# include <stdint.h>

/* adding support to allocate nodes in a memory pool */
# include "memory_pool.h"
# include "ft_memfunc.h"
# include "error_handling.h"

/* ixp: integer xor mempool list */

typedef struct s_ixpnode
{
	int					data;
	struct s_ixpnode	*xor_ptr;
}	t_ixpnode;

typedef struct s_ixplist
{
	t_ixpnode	*head;
	t_ixpnode	*tail;
	t_mpool		*pool;
	size_t		len;
}	t_ixplist;

t_ixplist	*ixplist_new(int elements, t_mpool *shared_pool);
void		ixplist_in_head(t_ixplist *list, int data);
void		ixplist_in_tail(t_ixplist *list, int data);
void		ixplist_del_head(t_ixplist *list);
void		ixplist_del_tail(t_ixplist *list);
void		ixplist_head_print(t_ixplist *list, void (*pnt)(int));
void		ixplist_tail_print(t_ixplist *list, void (*pnt)(int));
void		ixplist_destroy(t_ixplist **list, int keep_pool);

/* ixm: integer xor malloc list */

typedef struct s_ixmnode
{
	int					data;
	struct s_ixmnode	*xor_ptr;
}	t_ixmnode;

typedef struct s_ixmlist
{
	struct s_ixmnode	*head;
	struct s_ixmnode	*tail;
	size_t				len;
}	t_ixmlist;

t_ixmlist	*ixmlist_new(void);
void		ixmlist_in_head(t_ixmlist *list, int data);
void		ixmlist_in_tail(t_ixmlist *list, int data);
void		ixmlist_del_head(t_ixmlist *list);
void		ixmlist_del_tail(t_ixmlist *list);
void		ixmlist_head_print(t_ixmlist *list, void (*pnt)(int));
void		ixmlist_tail_print(t_ixmlist *list, void (*pnt)(int));
void		ixmlist_destroy(t_ixmlist **list);

#endif
