/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_sl_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:07:47 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:07:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_SL_LIST_H

# define INT_SL_LIST_H

# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>

# include "memory_pool.h"
# include "ft_memfunc.h"
# include "error_handling.h"

typedef struct s_ismnode
{
	int					data;
	struct s_ismnode	*next;
}	t_ismnode;

typedef struct s_ismlist
{
	t_ismnode	*head;
	t_ismnode	*tail;
	size_t		len;
}	t_ismlist;

t_ismlist	*ismlist_new(void);
int			ismlist_in_head(t_ismlist *list, int data);
int			ismlist_in_tail(t_ismlist *list, int data);
int			ismlist_find(t_ismlist *list, int target);
int			ismlist_removeif(t_ismlist *list, int target);
void		ismlist_del_head(t_ismlist *list);
void		ismlist_head_print(t_ismlist *list, void (*pnt)(int));
void		ismlist_destroy(t_ismlist **list);

/* function for faster hashset*/
int			hashset_ismlist_removefst(t_ismlist *list, int target);

/* falta adicionar suporte para memory pool */

#endif
