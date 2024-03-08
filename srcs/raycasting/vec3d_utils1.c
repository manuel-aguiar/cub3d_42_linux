/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:07:43 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 13:07:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	vec3d_len(t_vec3d vec)
{
	return (sqrt(fpow_2(vec.x) + fpow_2(vec.y) + fpow_2(vec.z)));
}

t_vec3d	vec3d_sub(t_vec3d first, t_vec3d second)
{
	return ((t_vec3d){second.x - first.x, second.y - first.y, \
		second.z - first.z});
}

t_vec3d	vec3d_get_dirvec(t_vec3d from, t_vec3d to)
{
	t_vec3d	direction;

	direction.x = to.x - from.x;
	direction.y = to.y - from.y;
	direction.z = to.z - from.z;
	return (direction);
}

t_vec2d	vec3d_get_xy_from_z(t_vec3d point, t_vec3d dir, float z)
{
	t_vec2d	new;
	float	times;

	times = (z - point.z) / dir.z;
	new.x = point.x + dir.x * times;
	new.y = point.y + dir.y * times;
	return (new);
}

float	vec3d_get_z_from_xy(t_vec3d point, t_vec3d dir, t_vec2d xy)
{
	float	times;
	float	z;

	if (ft_fabs(dir.x) > 0.001f)
		times = (xy.x - point.x) / dir.x;
	else
		times = (xy.y - point.y) / dir.y;
	z = point.z + dir.z * times;
	return (z);
}
