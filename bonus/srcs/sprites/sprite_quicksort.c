/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_quicksort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:46:18 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:46:18 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

int	sprite_qs_comp(t_sprite *first, t_sprite *second)
{
	return (first->dist < second->dist);
}

static void	swap(t_sprite **first, t_sprite **second)
{
	t_sprite	*temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

static int	partition(t_sprite **sprites, int low, int high, \
	int (*cmp)(t_sprite *, t_sprite *))
{
	t_sprite	*pivot;
	int			i;
	int			j;

	pivot = sprites[low];
	i = low - 1;
	j = high + 1;
	while (1)
	{
		i++;
		while (cmp(pivot, sprites[i]))
			i++;
		j--;
		while (cmp(sprites[j], pivot))
			j--;
		if (i >= j)
			return (j);
		swap(&sprites[i], &sprites[j]);
	}
}

static void	qs_recursion(t_sprite **sprites, int low, int high, \
	int (*cmp)(t_sprite *, t_sprite *))
{
	int	part;

	if (low < high)
	{
		part = partition(sprites, low, high, cmp);
		qs_recursion(sprites, low, part, cmp);
		qs_recursion(sprites, part + 1, high, cmp);
	}
}

void	sprite_qs_distance(t_sprite **sprites, int sprite_count, \
	int (*cmp)(t_sprite *, t_sprite *))
{
	qs_recursion(sprites, 0, sprite_count - 1, cmp);
}
