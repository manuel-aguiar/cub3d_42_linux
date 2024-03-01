/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 09:41:56 by codespace         #+#    #+#             */
/*   Updated: 2023/09/20 11:34:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_hashtable	*hashtable_init(int size, int (*hash_func)(void *),
		int (*key_compare)(void *, void *))
{
	t_hashtable	*table;

	table = malloc(sizeof(*table));
	if (!table)
		return (perror_msg_ptr("malloc", NULL));
	table->size = size;
	table->collision = ft_calloc(sizeof(*(table->collision)), table->size);
	if (!table->collision)
	{
		free(table);
		return (perror_msg_ptr("malloc", NULL));
	}
	table->hash_func = hash_func;
	table->key_compare = key_compare;
	return (table);
}

int	hashtable_contains(t_hashtable *table, void *key)
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
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	hashtable_insert(t_hashtable *table, void *key, void *value)
{
	int	index;

	if (!table || hashtable_contains(table, key))
		return (0);
	index = table->hash_func(key) % table->size;
	if (!table->collision[index])
	{
		table->collision[index] = htlist_new();
		if (!table->collision[index])
			return (perror_msg_int("malloc", 0));
	}
	if (!htlist_in_tail(table->collision[index], key, value))
		return (0);
	return (1);
}

int	hashtable_remove(t_hashtable *table, void *key, void (*del_key)(void *),
		void (*del_value)(void *))
{
	int			index;
	t_htnode	*cur;

	if (!table || !hashtable_contains(table, key))
		return (0);
	index = table->hash_func(key) % table->size;
	cur = table->collision[index]->head;
	while (cur)
	{
		if (table->key_compare(key, cur->key))
		{
			htlist_del_pair(table->collision[index], key, del_key, del_value);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

void	hashtable_destroy(t_hashtable **table, void (*del_key)(void *),
		void (*del_value)(void *))
{
	int			i;
	t_hashtable	*my_table;

	if (!table)
		return ;
	my_table = *table;
	i = 0;
	while (i < my_table->size)
	{
		htlist_destroy(&my_table->collision[i], del_key, del_value);
		i++;
	}
	free(my_table->collision);
	ft_free_set_null(table);
}
