/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolinwu_antialiasing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:45:33 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:45:33 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing_algos.h"

extern int	xiaolin_x_major(t_win *win, t_pixel *start, \
	t_pixel *end, t_xldata *data);
extern int	xiaolin_y_major(t_win *win, t_pixel *start, \
	t_pixel *end, t_xldata *data);

static int	xiaolin_diagonal(t_win *win, t_pixel *start, \
t_pixel *end, t_xldata *data)
{
	data->save = data->dy;
	while (--data->dy != 0)
	{
		data->colour = avg_colour(start->colour, end->colour, \
					data->dy, data->save);
		start->x += data->slope;
		start->y++;
		win->set_pixel(win, start->x, start->y, data->colour);
	}
	return (1);
}

static int	xiaolin_vertical(t_win *win, t_pixel *start, \
t_pixel *end, t_xldata *data)
{
	data->save = data->dy;
	while (data->dy-- != 0)
	{
		data->colour = avg_colour(start->colour, end->colour, \
					data->dy, data->save);
		start->y++;
		win->set_pixel(win, start->x, start->y, data->colour);
	}
	return (1);
}

static int	xiaolin_horizontal(t_win *win, t_pixel *start, \
t_pixel *end, t_xldata *data)
{
	data->save = data->dx;
	while (--data->dx != 0)
	{
		data->colour = avg_colour(start->colour, end->colour, \
					data->dx, data->save);
		start->x += data->slope;
		win->set_pixel(win, start->x, start->y, data->colour);
	}
	return (1);
}

int	xiaolinwu_line(t_win *win, t_pixel start, t_pixel end)
{
	t_xldata	data;

	if (start.y > end.y)
		swap_pixels(&start, &end);
	win->set_pixel(win, start.x, start.y, start.colour);
	data.dx = end.x - start.x;
	if (data.dx >= 0)
		data.slope = 1;
	else
	{
		data.slope = -1;
		data.dx = -data.dx;
	}
	data.dy = end.y - start.y;
	if (data.dx == 0)
		return (xiaolin_vertical(win, &start, &end, &data));
	if (data.dy == 0)
		return (xiaolin_horizontal(win, &start, &end, &data));
	if (data.dx == data.dy)
		return (xiaolin_diagonal(win, &start, &end, &data));
	data.err_acc = 0;
	if (data.dy > data.dx)
		return (xiaolin_y_major(win, &start, &end, &data));
	return (xiaolin_x_major(win, &start, &end, &data));
}
