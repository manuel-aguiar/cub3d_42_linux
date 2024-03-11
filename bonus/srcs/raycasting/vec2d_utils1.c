/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:46:38 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:46:38 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec2d	vec2d_add(t_vec2d	first, t_vec2d second)
{
	return ((t_vec2d){first.x + second.x, first.y + second.y});
}

t_vec2d	vec2d_sub(t_vec2d plus, t_vec2d minus)
{
	return ((t_vec2d){plus.x - minus.x, plus.y - minus.y});
}

t_vec2d	vec2d_multi(t_vec2d target, float multiplier)
{
	return ((t_vec2d){target.x * multiplier, target.y * multiplier});
}

float	vec2d_len(t_vec2d vector)
{
	return (sqrt(fpow_2(vector.x) + fpow_2(vector.y)));
}

t_vec2d	vec2d_norm(t_vec2d target, float vec2d_len)
{
	if (vec2d_len == 0)
		return ((t_vec2d){0, 0});
	return ((t_vec2d){target.x / vec2d_len, target.y / vec2d_len});
}
