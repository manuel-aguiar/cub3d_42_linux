/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2d_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:25:50 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 13:25:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec2d	vec2d_swap_coords(t_vec2d target)
{
	float	swap;

	swap = target.x;
	target.x = target.y;
	target.y = swap;
	return (target);
}

float	vec2d_distance(t_vec2d start, t_vec2d end)
{
	return (sqrt(fpow_2(end.x - start.x) + sqrt(fpow_2(end.y - start.y))));
}

t_vec2d	vec2d_product(t_vec2d first, t_vec2d second)
{
	return ((t_vec2d){first.x * second.x, first.y * second.y});
}

void	vec2d_swap(t_vec2d *first, t_vec2d *second)
{
	t_vec2d	swap;

	swap = *first;
	*first = *second;
	*second = swap;
}
