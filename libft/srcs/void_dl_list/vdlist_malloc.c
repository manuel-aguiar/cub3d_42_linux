/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_list_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:45:10 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 18:45:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "void_dl_list.h"

t_vdmnode	*new_vdmnode(void *data)
{
	t_vdmnode	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (perror_msg_ptr("malloc", NULL));
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_vdmlist	*vdmlist_new(void)
{
	t_vdmlist	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (perror_msg_ptr("malloc", NULL));
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
	return (list);
}

int	vdmlist_in_head(t_vdmlist *list, void *data)
{
	t_vdmnode	*new_node;

	if (!list)
		return (0);
	new_node = new_vdmnode(data);
	if (!new_node)
		return (0);
	if (list->head)
	{
		new_node->next = list->head;
		list->head->prev = new_node;
	}
	else
		list->tail = new_node;
	list->head = new_node;
	++(list->len);
	return (1);
}

int	vdmlist_in_tail(t_vdmlist *list, void *data)
{
	t_vdmnode	*new_node;

	if (!list)
		return (0);
	new_node = new_vdmnode(data);
	if (!new_node)
		return (0);
	if (list->tail)
	{
		new_node->prev = list->tail;
		list->tail->next = new_node;
	}
	else
		list->head = new_node;
	list->tail = new_node;
	++(list->len);
	return (1);
}

void	vdmlist_del_node(t_vdmlist *list, t_vdmnode *delete, \
						void (*del)(void *))
{
	if (!list || !(list->head) || !delete)
		return ;
	if (delete->prev)
		delete->prev->next = delete->next;
	else
		list->head = delete->next;
	if (delete->next)
		delete->next->prev = delete->prev;
	else
		list->tail = delete->prev;
	if (delete->data)
		del(delete->data);
	free(delete);
	--(list->len);
}
