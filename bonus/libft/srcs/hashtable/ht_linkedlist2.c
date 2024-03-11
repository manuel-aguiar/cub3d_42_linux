/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_linkedlist2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:45:01 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 11:23:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht_linkedlists.h"

static void	htnode_free(t_htnode *node, void (*del_key)(void *),
		void (*del_value)(void *))
{
	if (del_key)
		del_key(node->key);
	if (del_value)
		del_value(node->value);
	free(node);
}

void	htlist_del_pair(t_htlist *list, t_htnode *node, void (*del_key)(void *),
		void (*del_value)(void *))
{
	if (!list || !(list->head) || !node)
		return ;
	if (node == list->head)
	{
		if (list->head->next)
		{
			list->head->next->prev = NULL;
			list->head = list->head->next;
		}
		else
			list->head = NULL;
	}
	if (node == list->tail)
	{
		if (list->tail->prev)
		{
			list->tail->prev->next = NULL;
			list->tail = list->tail->prev;
		}
		else
			list->tail = NULL;
	}
	htnode_free(node, del_key, del_value);
	--(list->len);
}

void	htlist_destroy(t_htlist **list, void (*del_key)(void *),
		void (*del_value)(void *))
{
	t_htnode	*delete;
	t_htnode	*next;

	if (!list || !*list)
		return ;
	delete = (*list)->head;
	while (delete)
	{
		next = delete->next;
		if (del_key)
			del_key(delete->key);
		if (del_value)
			del_value(delete->value);
		free(delete);
		delete = next;
	}
	ft_free_set_null(list);
}
