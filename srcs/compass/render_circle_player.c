/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_circle_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:04:54 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 13:40:57 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

/*
Midpoint Circle algorithm, by calculating 1/8 of a circle, one can render the
full object by projecting coordinates

i will have to use a hashtable to store the circles coordinates to make
collision
detection easier. inner circle will not be moveable so the coordinates will
always
be valid. if the circle has atmost 200 height, i'll be storing 1600 bytes,
so it is a very small table and not drain much memory

hashtable for the square as well, for each single frame the square will be
the same for everyone except
the offset from where it starts off, with a couple of lookups i can check
the boundaries for
each scanline and print only what is needed
*/

void	set_four_pixels(t_win *win, int x, int y, t_render_circ *ren)
{
	t_hori_line	draw;

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
	if (ren->with_line)
	{
		draw.color = ren->color;
		draw.min_x = ren->centre.x - x;
		draw.max_x = ren->centre.x + x;
		draw.y = ren->centre.y + y;
		draw_horizontal_line(win, &draw);
		draw.y = ren->centre.y - y;
		draw_horizontal_line(win, &draw);
	}
}

void	render_empty_circle_with_aa(t_win *win, t_pixel centre, \
								int radius, int color)
{
	t_render_circ	ren;
	int				x;
	float			y;

	ren.centre = centre;
	ren.rad_sqr = radius * radius;
	ren.quarter = round(ren.rad_sqr / sqrt(ren.rad_sqr + ren.rad_sqr));
	ren.color = color;
	ren.with_line = false;
	x = 0;
	while (x <= ren.quarter)
	{
		y = radius * sqrt(1 - x * x / (float)ren.rad_sqr);
		ren.error = y - (int)(y);
		set_four_pixels(win, x, (int)(y), &ren);
		set_four_pixels(win, (int)(y), x, &ren);
		ren.error = 1 - ren.error;
		set_four_pixels(win, x, (int)(y) + 1, &ren);
		set_four_pixels(win, (int)(y) + 1, x, &ren);
		x++;
	}
}
