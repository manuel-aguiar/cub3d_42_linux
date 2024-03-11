/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_linkedlist1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:45:10 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 11:28:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht_linkedlists.h"

t_htnode	*new_htnode(void *key, void *value)
{
	t_htnode	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (perror_msg_ptr("malloc", NULL));
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_htlist	*htlist_new(void)
{
	t_htlist	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (perror_msg_ptr("malloc", NULL));
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
	return (list);
}

int	htlist_in_tail(t_htlist *list, void *key, void *value)
{
	t_htnode	*new_node;

	if (!list)
		return (0);
	new_node = new_htnode(key, value);
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
