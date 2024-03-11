/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_list_malloc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:45:01 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:45:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "void_dl_list.h"

static void	vdmlist_removeif_help(t_vdmlist *list, t_vdmnode *cur, \
									void (*del)(void *))
{
	if (cur->prev && list->len > 1)
		cur->prev->next = cur->next;
	else
	{
		list->head = cur->next;
		cur->next->prev = NULL;
	}
	if (cur->next && list->len > 1)
		cur->next->prev = cur->prev;
	else
	{
		list->tail = cur->prev;
		cur->prev->next = NULL;
	}
	if (del && cur->data)
		del(cur->data);
	free(cur);
	--(list->len);
}

void	vdmlist_remove_if(t_vdmlist *list, void *data, \
					int (*cmp)(void *, void *), void (*del)(void *))
{
	t_vdmnode	*cur;
	t_vdmnode	*next;

	if (!list || !list->head)
		return ;
	cur = list->head;
	while (cur)
	{
		next = cur->next;
		if (!cmp(cur->data, data))
		{
			if (list->len == 1)
			{
				if (del && cur->data)
					del(cur->data);
				free(cur);
				list->head = NULL;
				list->tail = NULL;
				--(list->len);
			}
			else
				vdmlist_removeif_help(list, cur, del);
		}
		cur = next;
	}
}

void	vdmlist_del_head(t_vdmlist *list, void (*del)(void *))
{
	t_vdmnode	*cur;

	if (!list || !(list->head))
		return ;
	cur = list->head;
	if (cur->next)
		cur->next->prev = NULL;
	else
		list->tail = NULL;
	list->head = cur->next;
	if (del)
		del(cur->data);
	free(cur);
	--(list->len);
}

void	vdmlist_del_tail(t_vdmlist *list, void (*del)(void *))
{
	t_vdmnode	*cur;

	if (!list || !(list->tail))
		return ;
	cur = list->tail;
	if (cur->prev)
		cur->prev->next = NULL;
	else
		list->head = NULL;
	list->tail = cur->prev;
	if (del)
		del(cur->data);
	free(cur);
	--(list->len);
}

void	vdmlist_destroy(t_vdmlist **list, void (*del)(void *))
{
	t_vdmnode	*delete;
	t_vdmnode	*next;

	if (!list || !*list)
		return ;
	delete = (*list)->head;
	while (delete)
	{
		next = delete->next;
		if (del)
			del(delete->data);
		free(delete);
		delete = next;
	}
	ft_free_set_null(list);
}
