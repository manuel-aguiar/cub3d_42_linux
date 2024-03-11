/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:56 by codespace         #+#    #+#             */
/*   Updated: 2024/03/07 13:38:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3d	vec3d_norm(t_vec3d target, float vec3d_len)
{
	if (vec3d_len == 0)
		return ((t_vec3d){0, 0, 0});
	return ((t_vec3d){target.x / vec3d_len, target.y / vec3d_len, \
		target.z / vec3d_len});
}
