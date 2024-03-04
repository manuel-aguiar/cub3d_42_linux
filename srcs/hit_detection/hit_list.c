/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:11:55 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/04 16:54:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit_detection.h"

void	hitlist_in_head(t_hitlist *list, t_hitnode *insert)
{
	if (list->head)
	{
		if (insert->sprite == list->head->sprite)
			return ;
		insert->next = list->head;
		list->head->prev = insert;
	}
	else
		list->tail = insert;
	list->head = insert;
	++(list->len);
}

void	hitlist_in_tail(t_hitlist *list, t_hitnode *insert)
{
	if (list->tail)
	{
		if (insert->sprite == list->tail->sprite)
			return ;
		insert->prev = list->tail;
		list->tail->next = insert;
	}
	else
		list->head = insert;
	list->tail = insert;
	++(list->len);
}

void	hitlist_del_head(t_hitlist *list)
{
	t_hitnode	*cur;

	if (!list->head)
		return ;
	cur = list->head;
	if (cur->next)
		cur->next->prev = NULL;
	else
		list->tail = NULL;
	list->head = cur->next;
	--(list->len);
}

void	hitlist_del_tail(t_hitlist *list)
{
	t_hitnode	*cur;

	if (!(list->tail))
		return ;
	cur = list->tail;
	if (cur->prev)
		cur->prev->next = NULL;
	else
		list->head = NULL;
	list->tail = cur->prev;
	--(list->len);
}
