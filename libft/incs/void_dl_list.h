/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_dl_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:07:43 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:07:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOID_DL_LIST_H

# define VOID_DL_LIST_H

# include <stdlib.h>
# include <stdint.h>

# include "memory_pool.h"
# include "ft_memfunc.h"
# include "error_handling.h"

typedef struct s_vdmnode
{
	void				*data;
	struct s_vdmnode	*next;
	struct s_vdmnode	*prev;
}	t_vdmnode;

typedef struct s_vdmlist
{
	t_vdmnode	*head;
	t_vdmnode	*tail;
	size_t		len;
}	t_vdmlist;

t_vdmlist	*vdmlist_new(void);
int			vdmlist_in_head(t_vdmlist *list, void *data);
int			vdmlist_in_tail(t_vdmlist *list, void *data);
int			vdmlist_find(t_vdmlist *list, void *data, \
int (*cmp)(void *, void *));
void		vdmlist_del_node(t_vdmlist *list, t_vdmnode *delete, \
void (*del)(void *));
void		vdmlist_remove_if(t_vdmlist *list, void *data, \
int (*cmp)(void *, void *), void (*del)(void *));
void		vdmlist_del_head(t_vdmlist *list, void (*del)(void *));
void		vdmlist_del_tail(t_vdmlist *list, void (*del)(void *));
void		vdmlist_head_print(t_vdmlist *list, void (*pnt)(void *));
void		vdmlist_tail_print(t_vdmlist *list, void (*pnt)(void *));
void		vdmlist_destroy(t_vdmlist **list, void (*del)(void *));

/*
applying a memory pool to doubly linked list in order to improve locality of data
and reduce the number of system calls to malloc and free as nodes are added
and delete from the list.
*/

typedef struct s_vdpnode
{
	void				*data;
	struct s_vdpnode	*next;
	struct s_vdpnode	*prev;
}	t_vdpnode;

typedef struct s_vdplist
{
	t_vdpnode	*head;
	t_vdpnode	*tail;
	t_mpool		*pool;
	size_t		len;
}	t_vdplist;

/* incomplete, must adjust list destruction*/
t_vdplist	*vdplist_new(int elements, t_mpool *shared_pool);
void		vdplist_in_head(t_vdplist *list, void *data);
void		vdplist_in_tail(t_vdplist *list, void *data);
void		vdplist_del_head(t_vdplist *list, void (*del)(void *));
void		vdplist_del_tail(t_vdplist *list, void (*del)(void *));
void		vdplist_head_print(t_vdplist *list, void (*pnt)(void *));
void		vdplist_tail_print(t_vdplist *list, void (*pnt)(void *));
void		vdplist_delall_content(t_vdplist *list, void (*del)(void *));
void		vdplist_destroy(t_vdplist **list, int keep_pool, \
void (*del)(void *));

#endif
