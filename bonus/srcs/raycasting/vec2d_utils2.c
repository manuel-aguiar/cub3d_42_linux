/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:46:34 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:46:34 by mmaria-d         ###   ########.fr       */
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
