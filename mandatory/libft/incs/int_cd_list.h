/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_cd_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:07:38 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:07:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_CD_LIST_H

# define INT_CD_LIST_H

/* This is header provides declarations for the implementation of a
circular doubly linkedlist*/

# include <stdlib.h>
# include <stdint.h>

# include "memory_pool.h"
# include "ft_memfunc.h"
# include "error_handling.h"

typedef struct s_icpnode
{
	int					data;
	struct s_icpnode	*next;
	struct s_icpnode	*prev;
}	t_icpnode;

typedef struct s_icplist
{
	t_icpnode	*pivot;
	t_mpool		*pool;
	int			len;
}	t_icplist;

t_icplist	*icplist_new(int elements, t_mpool *shared_pool);
void		icplist_in_head(t_icplist *list, int data);
void		icplist_in_tail(t_icplist *list, int data);
void		icplist_del_head(t_icplist *list);
void		icplist_del_tail(t_icplist *list);
void		icplist_head_print(t_icplist *list, void (*pnt)(int));
void		icplist_tail_print(t_icplist *list, void (*pnt)(int));
void		icplist_destroy(t_icplist **list, int keep_pool);

/* falta adicionar suporte para alocar com malloc */

#endif
