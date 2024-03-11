/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_list_malloc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:58:48 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 14:58:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_xor_list.h"

t_ixmnode	*xor_func(t_ixmnode *prev, t_ixmnode *next);

void	ixmlist_del_head(t_ixmlist *list)
{
	t_ixmnode	*cur;
	t_ixmnode	*next;

	if (!list || !(list->head))
		return ;
	cur = list->head;
	next = xor_func(cur->xor_ptr, NULL);
	if (next)
		next->xor_ptr = xor_func(cur, next->xor_ptr);
	else
		list->tail = NULL;
	list->head = next;
	free(cur);
	--(list->len);
}

void	ixmlist_del_tail(t_ixmlist *list)
{
	t_ixmnode	*cur;
	t_ixmnode	*prev;

	if (!list || !(list->tail))
		return ;
	cur = list->tail;
	prev = xor_func(cur->xor_ptr, NULL);
	if (prev)
		prev->xor_ptr = xor_func(prev->xor_ptr, cur);
	else
		list->head = NULL;
	list->tail = prev;
	free(cur);
	--(list->len);
}

void	ixmlist_destroy(t_ixmlist **list)
{
	if (!list || !*list)
		return ;
	while ((*list)->head)
		ixmlist_del_head(*list);
	ft_free_set_null(list);
}
