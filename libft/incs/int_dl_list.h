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

#ifndef INT_DL_LIST_H

# define INT_DL_LIST_H

# include <stdlib.h>
# include <stdint.h>

# include "memory_pool.h"
# include "ft_memfunc.h"
# include "error_handling.h"

typedef struct s_idmnode
{
	int					data;
	struct s_idmnode	*next;
	struct s_idmnode	*prev;
}	t_idmnode;

typedef struct s_idmlist
{
	t_idmnode	*head;
	t_idmnode	*tail;
	size_t		len;
}	t_idmlist;

t_idmlist	*idmlist_new(void);
int			idmlist_in_head(t_idmlist *list, int data);
int			idmlist_in_tail(t_idmlist *list, int data);
int			idmlist_find(t_idmlist *list, int target);
void		idmlist_remove_if(t_idmlist *list, int target);
void		idmlist_del_head(t_idmlist *list);
void		idmlist_del_tail(t_idmlist *list);
void		idmlist_head_print(t_idmlist *list, void (*pnt)(int));
void		idmlist_tail_print(t_idmlist *list, void (*pnt)(int));
void		idmlist_destroy(t_idmlist **list);

/*
applying a memory pool to doubly linked list in order to improve locality of data
and reduce the number of system calls to malloc and free as nodes are added
and delete from the list.
*/

typedef struct s_idpnode
{
	int					data;
	struct s_idpnode	*next;
	struct s_idpnode	*prev;
}	t_idpnode;

typedef struct s_idplist
{
	t_idpnode	*head;
	t_idpnode	*tail;
	t_mpool		*pool;
	size_t		len;
}	t_idplist;

t_idplist	*idplist_new(int elements, t_mpool *shared_pool);
void		idplist_in_head(t_idplist *list, int data);
void		idplist_in_tail(t_idplist *list, int data);
void		idplist_del_head(t_idplist *list);
void		idplist_del_tail(t_idplist *list);
void		idplist_head_print(t_idplist *list, void (*pnt)(int));
void		idplist_tail_print(t_idplist *list, void (*pnt)(int));
void		idplist_destroy(t_idplist **list, int keep_pool);

#endif
