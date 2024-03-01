/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:59:09 by codespace         #+#    #+#             */
/*   Updated: 2024/02/06 09:45:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

int	hashtable_return_value(t_hashtable *table, void *key, void *place_res)
{
	int			index;
	t_htnode	*cur;

	if (!table)
		return (0);
	index = table->hash_func(key) % table->size;
	if (!table->collision[index])
		return (0);
	cur = table->collision[index]->head;
	while (cur)
	{
		if (!table->key_compare(key, cur->key))
		{
			*(void **)place_res = cur->value;
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}
