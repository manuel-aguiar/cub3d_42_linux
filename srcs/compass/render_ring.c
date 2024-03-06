/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:48:21 by marvin            #+#    #+#             */
/*   Updated: 2024/01/21 11:48:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

void	setpixel_inner(t_win *win, int x, int y, t_render_circ *ren);

static inline void	setup_ring_draw(t_compass *comp, t_render_circ *ren)
{
	ren->centre = comp->centre;
	ren->comp = comp;
	ren->radius = comp->radius;
	ren->color = comp->color;
	ren->rad_sqr = ren->radius * ren->radius;
	ren->quarter = round(ren->radius / sqrt(ren->radius + ren->radius));
	ft_memcpy(&ren->c_min_max, &comp->inner.min_max, \
		sizeof(ren->c_min_max[0]) * MM_SIZE);
	ren->c_min_max[MM_MIN_X] += comp->centre.x;
	ren->c_min_max[MM_MAX_X] += comp->centre.x;
	ren->c_min_max[MM_MIN_Y] += comp->centre.y;
	ren->c_min_max[MM_MAX_Y] += comp->centre.y;
}

void	draw_ring_to_inner_circle(t_win *win, t_compass *comp)
{
	t_render_circ	ren;
	int				x;
	float			y;

	setup_ring_draw(comp, &ren);
	x = 0;
	while (x <= ren.quarter)
	{
		y = ren.radius * sqrt(1 - x * x / (float)ren.rad_sqr);
		ren.error = y - (int)(y);
		ren.with_line = true;
		setpixel_inner(win, x, (int)(y), &ren);
		setpixel_inner(win, (int)(y), x, &ren);
		ren.error = 1 - ren.error;
		ren.with_line = false;
		setpixel_inner(win, x, (int)(y) + 1, &ren);
		setpixel_inner(win, (int)(y) + 1, x, &ren);
		x++;
	}
}
