/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:10:24 by cjoao-me          #+#    #+#             */
/*   Updated: 2024/03/08 14:10:24 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "math.h"
# include "generic_utils.h"
# include "pixel_point.h"

typedef struct s_vec2d
{
	float	x;
	float	y;
}	t_vec2d;

typedef struct s_vec3d
{
	float	x;
	float	y;
	float	z;
}	t_vec3d;

//2D vector functions
t_vec2d		vec2d_add(t_vec2d	first, t_vec2d second);
t_vec2d		vec2d_sub(t_vec2d plus, t_vec2d minus);
t_vec2d		vec2d_multi(t_vec2d target, float multiplier);
float		vec2d_len(t_vec2d vector);
t_vec2d		vec2d_norm(t_vec2d target, float vec2d_len);
t_vec2d		vec2d_swap_coords(t_vec2d target);
float		vec2d_distance(t_vec2d start, t_vec2d end);
t_vec2d		vec2d_product(t_vec2d first, t_vec2d second);
void		vec2d_swap(t_vec2d *first, t_vec2d *second);

//3D vector functions
t_vec2d		vec3d_get_xy_from_z(t_vec3d point, t_vec3d dir, float z);
float		vec3d_get_z_from_xy(t_vec3d point, t_vec3d dir, t_vec2d xy);
float		vec3d_len(t_vec3d vec);
t_vec3d		vec3d_sub(t_vec3d first, t_vec3d second);
t_vec3d		vec3d_get_dirvec(t_vec3d from, t_vec3d to);
t_vec3d		vec3d_norm(t_vec3d target, float vec3d_len);

#endif
