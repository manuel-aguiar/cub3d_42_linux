/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashset_int_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:54:22 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 15:54:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashset_int.h"

int	hashset_ismlist_removefst(t_ismlist *list, int target)
{
	t_ismnode	*cur;
	t_ismnode	*prev;
	t_ismnode	dummy;

	if (!list || !list->head || !(list->len))
		return (0);
	prev = &dummy;
	cur = list->head;
	while (cur && cur->data != target)
	{
		prev->next = cur;
		cur = cur->next;
		prev = prev->next;
	}
	if (cur)
	{
		prev->next = cur->next;
		free(cur);
		cur = NULL;
		if (!prev->next)
			list->tail = prev;
		list->head = (dummy.next);
		return (1);
	}
	return (0);
}

void	ihs_table_print(t_ihs_table *table, void (*pnt)(int))
{
	int	i;
	int	size;

	if (!table || !pnt)
		return ;
	if (table->zero)
		pnt(0);
	i = 0;
	size = table->size;
	while (i < size)
	{
		if (table->data[i])
			pnt(table->data[i]);
		if (table->collision[i])
			ismlist_head_print(table->collision[i], pnt);
		i++;
	}
}

void	ihs_free_table(t_ihs_table **table)
{
	int			i;
	t_ihs_table	*destroy;

	if (!table)
	{
		return ;
	}
	destroy = *table;
	i = 0;
	while (i < destroy->size)
	{
		if (destroy->collision[i])
			ismlist_destroy(&(destroy->collision[i]));
		i++;
	}
	free(destroy->data);
	free(destroy->collision);
	ft_free_set_null(table);
}

int	ihs_remove_collision(t_ihs_table *table, int index, int key)
{
	int	remove_count;

	remove_count = hashset_ismlist_removefst(table->collision[index], key);
	if (table->collision[index]->len == 0)
		ismlist_destroy(&(table->collision[index]));
	if (!remove_count)
		return (0);
	return (1);
}
