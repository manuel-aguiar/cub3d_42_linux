/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_list_malloc_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:14:59 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/05/31 20:15:34 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_sl_list.h"

void	ismlist_head_print(t_ismlist *list, void (*pnt)(int))
{
	t_ismnode	*cur;

	if (!list)
		return ;
	cur = list->head;
	while (cur)
	{
		pnt(cur->data);
		cur = cur->next;
	}
}
