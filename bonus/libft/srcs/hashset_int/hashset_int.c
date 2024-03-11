/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashset_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:35:34 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 15:35:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashset_int.h"

int	hashset_ismlist_removefst(t_ismlist *list, int target);

int	ihs_remove_collision(t_ihs_table *table, int index, int key);

t_ihs_table	*ihs_init_table(int size)
{
	t_ihs_table	*table;
	t_ismlist	**collision;
	int			*array;

	table = malloc(sizeof(*table));
	if (!table)
		return (perror_msg_ptr("malloc", NULL));
	array = ft_calloc(sizeof(*array), size);
	table->data = array;
	table->size = size;
	table->zero = 0;
	collision = ft_calloc(sizeof(*collision), size);
	table->collision = collision;
	if (!collision || !array)
		ihs_free_table(&table);
	return (table);
}

int	ihs_hash_function(int key, int tab_size)
{
	return (ft_abs(key) % tab_size);
}

int	ihs_contains(t_ihs_table *table, int key)
{
	int	index;

	if (!table)
		return (-1);
	if (key == 0)
	{
		if (!table->zero)
			return (0);
		return (1);
	}
	index = ihs_hash_function(key, table->size);
	if (table->data[index] == key)
		return (1);
	if (table->collision[index] && ismlist_find(table->collision[index], key))
		return (1);
	return (0);
}

int	ihs_insert(t_ihs_table *table, int key)
{
	int	index;

	if (!table)
		return (-1);
	if (ihs_contains(table, key))
		return (0);
	if (key == 0)
	{
		table->zero = 1;
		return (1);
	}
	index = ihs_hash_function(key, table->size);
	if (!table->data[index])
		table->data[index] = key;
	else
	{
		if (!table->collision[index])
			table->collision[index] = ismlist_new();
		ismlist_in_head(table->collision[index], key);
	}
	return (1);
}

int	ihs_remove(t_ihs_table *table, int key)
{
	int	index;

	if (!table)
		return (-1);
	if (key == 0)
	{
		if (!table->zero)
			return (0);
		table->zero = 0;
		return (1);
	}
	index = ihs_hash_function(key, table->size);
	if (table->data[index] == key)
		table->data[index] = 0;
	else if (table->collision[index])
		return (ihs_remove_collision(table, index, key));
	else
		return (0);
	return (1);
}
