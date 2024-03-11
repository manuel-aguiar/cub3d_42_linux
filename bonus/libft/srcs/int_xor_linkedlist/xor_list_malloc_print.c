/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_list_malloc_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:22:19 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/05/31 21:37:10 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_xor_list.h"

t_ixmnode	*xor_func(t_ixmnode *prev, t_ixmnode *next);

void	ixmlist_head_print(t_ixmlist *list, void (*pnt)(int))
{
	t_ixmnode	*cur;
	t_ixmnode	*prev;
	t_ixmnode	*next;

	if (!list)
		return ;
	cur = list->head;
	prev = NULL;
	while (cur)
	{
		pnt(cur->data);
		next = xor_func(prev, cur->xor_ptr);
		prev = cur;
		cur = next;
	}
}

void	ixmlist_tail_print(t_ixmlist *list, void (*pnt)(int))
{
	t_ixmnode	*cur;
	t_ixmnode	*prev;
	t_ixmnode	*next;

	if (!list)
		return ;
	cur = list->tail;
	next = NULL;
	while (cur)
	{
		pnt(cur->data);
		prev = xor_func(next, cur->xor_ptr);
		next = cur;
		cur = prev;
	}
}
