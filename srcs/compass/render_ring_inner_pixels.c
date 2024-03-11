/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ring_inner_pixels.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:18:34 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 13:41:24 by mmaria-d         ###   ########.fr       */
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

void	line_with_blur(t_win *win, int x, t_render_circ *ren)
{
	t_compass	*comp;
	int			index;

	comp = ren->comp;
	index = ren->draw.y - comp->inner.centre.y + comp->inner.radius;
	ren->draw.min_x = ren->centre.x - x;
	ren->draw.max_x = comp->circle_x_lim[index].min + comp->inner.centre.x;
	draw_horizontal_line(win, &ren->draw);
	if (comp->blur_on == true)
	{
		ren->draw.min_x = comp->circle_x_lim[index].min + comp->inner.centre.x;
		ren->draw.max_x = comp->circle_x_lim[index].max + comp->inner.centre.x;
		drop_the_blur(win, comp, &ren->draw);
	}
	ren->draw.min_x = comp->circle_x_lim[index].max + comp->inner.centre.x;
	ren->draw.max_x = ren->centre.x + x;
	draw_horizontal_line(win, &ren->draw);
}

void	full_line(t_win *win, int x, t_render_circ *ren)
{
	ren->draw.min_x = ren->centre.x - x;
	ren->draw.max_x = ren->centre.x + x;
	draw_horizontal_line(win, &ren->draw);
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
	place_circle_aa(win, x, y, ren);
	ren->draw.color = ren->color;
	if (!ren->with_line)
		return ;
	ren->draw.y = ren->centre.y + y;
	if (ren->draw.y > ren->c_min_max[MM_MAX_Y])
		full_line(win, x, ren);
	else
		line_with_blur(win, x, ren);
	ren->draw.y = ren->centre.y - y;
	if (ren->draw.y < ren->c_min_max[MM_MIN_Y])
		full_line(win, x, ren);
	else if (y)
		line_with_blur(win, x, ren);
}
