/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idl_list_malloc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:33:08 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/05/31 21:33:08 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_dl_list.h"

static void	idmlist_removeif_helper(t_idmlist *list, t_idmnode *cur)
{
	if (cur->prev)
		cur->prev->next = cur->next;
	else
	{
		list->head = cur->next;
		cur->next->prev = NULL;
	}
	if (cur->next)
		cur->next->prev = cur->prev;
	else
	{
		list->tail = cur->prev;
		cur->prev->next = NULL;
	}
	free(cur);
	--(list->len);
}

void	idmlist_remove_if(t_idmlist *list, int target)
{
	t_idmnode	*cur;
	t_idmnode	*next;

	if (!list || !list->head)
		return ;
	cur = list->head;
	while (cur)
	{
		next = cur->next;
		if (cur->data == target)
			idmlist_removeif_helper(list, cur);
		cur = next;
	}
}

void	idmlist_del_head(t_idmlist *list)
{
	t_idmnode	*cur;

	if (!list || !(list->head))
		return ;
	cur = list->head;
	if (cur->next)
		cur->next->prev = NULL;
	else
		list->tail = NULL;
	list->head = cur->next;
	free(cur);
	--(list->len);
}

void	idmlist_del_tail(t_idmlist *list)
{
	t_idmnode	*cur;

	if (!list || !(list->tail))
		return ;
	cur = list->tail;
	if (cur->prev)
		cur->prev->next = NULL;
	else
		list->head = NULL;
	list->tail = cur->prev;
	free(cur);
	--(list->len);
}

void	idmlist_destroy(t_idmlist **list)
{
	t_idmnode	*del;
	t_idmnode	*next;

	if (!list || !*list)
		return ;
	del = (*list)->head;
	while (del)
	{
		next = del->next;
		free(del);
		del = next;
	}
	ft_free_set_null(list);
}
