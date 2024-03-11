/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_list_malloc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:39:23 by marvin            #+#    #+#             */
/*   Updated: 2023/05/31 20:15:31 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_sl_list.h"

int	ismlist_find(t_ismlist *list, int target)
{
	t_ismnode	*cur;

	if (!list || !(list->head))
		return (0);
	cur = list->head;
	while (cur)
	{
		if (cur->data == target)
			return (1);
		cur = cur->next;
	}
	return (0);
}

static t_ismnode	*ismlist_removeif_helper(t_ismlist *list, t_ismnode *node)
{
	t_ismnode	*delete;

	delete = node;
	node = node->next;
	free(delete);
	delete = NULL;
	--(list->len);
	return (node);
}

int	ismlist_removeif(t_ismlist *list, int target)
{
	t_ismnode	*cur;
	t_ismnode	dummy;
	size_t		init_len;

	if (!list || !list->head || !(list->len))
		return (0);
	list->tail = &dummy;
	cur = list->head;
	init_len = list->len;
	while (cur)
	{
		if (cur->data == target)
			cur = ismlist_removeif_helper(list, cur);
		else
		{
			list->tail->next = cur;
			cur = cur->next;
			list->tail = list->tail->next;
		}
	}
	list->tail->next = NULL;
	list->head = (dummy.next);
	return ((int)(init_len - list->len));
}

void	ismlist_del_head(t_ismlist *list)
{
	t_ismnode	*cur;

	if (!list || !(list->head))
		return ;
	cur = list->head;
	if (!cur->next)
		list->tail = NULL;
	list->head = cur->next;
	free(cur);
	--(list->len);
}

void	ismlist_destroy(t_ismlist **list)
{
	t_ismnode	*del;
	t_ismnode	*next;

	if (!list || !*list)
		return ;
	del = (*list)->head;
	while (del)
	{
		next = del->next;
		free(del);
		del = next;
	}
	free(*list);
	*list = NULL;
}
