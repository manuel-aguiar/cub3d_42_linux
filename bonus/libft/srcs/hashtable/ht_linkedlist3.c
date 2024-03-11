/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_linkedlist3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:02:41 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/09/20 11:23:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ht_linkedlists.h"

void	htlist_head_print(t_htlist *list, void (*pnt)(void *))
{
	t_htnode	*cur;

	if (!list)
		return ;
	cur = list->head;
	while (cur)
	{
		pnt(cur->key);
		cur = cur->next;
	}
}
