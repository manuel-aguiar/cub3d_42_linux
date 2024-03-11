/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isl_list_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:11:55 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/09/16 13:06:39 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_sl_list.h"

t_ismnode	*ismnode_new(int nbr)
{
	t_ismnode	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (perror_msg_ptr("malloc", NULL));
	new->data = nbr;
	new->next = NULL;
	return (new);
}

t_ismlist	*ismlist_new(void)
{
	t_ismlist	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (perror_msg_ptr("malloc", NULL));
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
	return (list);
}

int	ismlist_in_head(t_ismlist *list, int data)
{
	t_ismnode	*new_node;

	if (!list)
		return (0);
	new_node = ismnode_new(data);
	if (!new_node)
		return (0);
	if (list->head)
		new_node->next = list->head;
	else
		list->tail = new_node;
	list->head = new_node;
	++(list->len);
	return (1);
}

int	ismlist_in_tail(t_ismlist *list, int data)
{
	t_ismnode	*new_node;

	if (!list)
		return (0);
	new_node = ismnode_new(data);
	if (!new_node)
		return (0);
	if (list->tail)
		list->tail->next = new_node;
	else
		list->head = new_node;
	list->tail = new_node;
	++(list->len);
	return (1);
}
