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

void	drop_the_blur(t_win *win, t_compass *comp, t_hori_line *draw)
{
	t_comp_blur	*blur;
	int			blur_y;
	int			blur_x;

	if (!comp->blur_on)
		return ;
	blur = &comp->blur;
	blur_y = comp->radius + draw->y - comp->centre.y;
	blur_x = comp->radius + draw->min_x - comp->centre.x;
	while (draw->min_x < draw->max_x)
	{
		blur_x = comp->radius + draw->min_x - comp->centre.x;
		win->set_pixel(win, draw->min_x++, draw->y, \
			blur->verti_blur[blur_y * blur->blur_height + blur_x]);
	}
}

void	place_circle_aa(t_win *win, int x, int y, t_render_circ *ren)
{
	win->set_pixel(win, ren->centre.x + x, ren->centre.y + y, \
	gamma_average(win->get_pixel(win, ren->centre.x + x, ren->centre.y + y), \
	ren->color, ren->error));
	win->set_pixel(win, ren->centre.x - x, ren->centre.y + y, \
	gamma_average(win->get_pixel(win, ren->centre.x - x, ren->centre.y + y), \
	ren->color, ren->error));
	win->set_pixel(win, ren->centre.x + x, ren->centre.y - y, \
	gamma_average(win->get_pixel(win, ren->centre.x + x, ren->centre.y - y), \
	ren->color, ren->error));
	win->set_pixel(win, ren->centre.x - x, ren->centre.y - y, \
	gamma_average(win->get_pixel(win, ren->centre.x - x, ren->centre.y - y), \
	ren->color, ren->error));
}

void	setpixel_inner(t_win *win, int x, int y, t_render_circ *ren)
{
	t_compass	*comp;
	t_hori_line	draw;
	int			index;

	place_circle_aa(win, x, y, ren);
	draw.color = ren->color;
	if (!ren->with_line)
		return ;
	comp = ren->comp;
	draw.y = ren->centre.y + y;
	if (ren->centre.y + y > ren->c_min_max[MM_MAX_Y])
	{
		draw.min_x = ren->centre.x - x;
		draw.max_x = ren->centre.x + x;
		draw_horizontal_line(win, &draw);
	}
	else
	{
		index = ren->centre.y + y - comp->inner.centre.y + comp->inner.radius;
		draw.min_x = ren->centre.x - x;
		draw.max_x = comp->circle_x_lim[index].min + comp->inner.centre.x;
		draw_horizontal_line(win, &draw);
		if (comp->blur_on == true)
		{
			draw.min_x = comp->circle_x_lim[index].min + comp->inner.centre.x;
			draw.max_x = comp->circle_x_lim[index].max + comp->inner.centre.x;
			drop_the_blur(win, comp, &draw);
		}
		draw.min_x = comp->circle_x_lim[index].max + comp->inner.centre.x;
		draw.max_x = ren->centre.x + x;
		draw_horizontal_line(win, &draw);
	}
	draw.y = ren->centre.y - y;
	if (ren->centre.y - y < ren->c_min_max[MM_MIN_Y])
	{
		draw.min_x = ren->centre.x - x;
		draw.max_x = ren->centre.x + x;
		draw_horizontal_line(win, &draw);
	}
	else if (y)
	{
		index = ren->centre.y - y - comp->inner.centre.y + comp->inner.radius;
		draw.min_x = ren->centre.x - x;
		draw.max_x = comp->circle_x_lim[index].min + comp->inner.centre.x;
		draw_horizontal_line(win, &draw);
		if (comp->blur_on == true)
		{
			draw.min_x = comp->circle_x_lim[index].min + comp->inner.centre.x;
			draw.max_x = comp->circle_x_lim[index].max + comp->inner.centre.x;
			drop_the_blur(win, comp, &draw);
		}
		draw.min_x = comp->circle_x_lim[index].max + comp->inner.centre.x;
		draw.max_x = ren->centre.x + x;
		draw_horizontal_line(win, &draw);
	}
}

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
