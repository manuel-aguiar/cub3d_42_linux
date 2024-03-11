/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolinwu_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:45:38 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:45:38 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing_algos.h"

int	xiaolin_x_major(t_win *win, t_pixel *start, t_pixel *end, t_xldata *data)
{
	data->err_adj = ((t_ulong)data->dy << 16) / (t_ulong)data->dx;
	data->save = data->dx;
	while (--data->dx)
	{
		data->err_temp = data->err_acc;
		data->err_acc += data->err_adj;
		if (data->err_acc <= data->err_temp)
			start->y++;
		start->x += data->slope;
		data->colour = avg_colour(start->colour, end->colour, \
					data->dx, data->save);
		win->set_pixel(win, start->x, start->y, \
			gamma_average(win->get_pixel(win, start->x, \
			start->y), data->colour, (float)data->err_acc / (float)USHRT_MAX));
		win->set_pixel(win, start->x, start->y + 1, \
			gamma_average(win->get_pixel(win, \
			start->x, start->y + 1), data->colour, \
			(float)(USHRT_MAX - data->err_acc) / (float)USHRT_MAX));
	}
	win->set_pixel(win, end->x, end->y, end->colour);
	return (1);
}

int	xiaolin_y_major(t_win *win, t_pixel *start, t_pixel *end, t_xldata *data)
{
	data->err_adj = ((t_ulong)data->dx << 16) / (t_ulong)data->dy;
	data->save = data->dy;
	while (--data->dy)
	{
		data->err_temp = data->err_acc;
		data->err_acc += data->err_adj;
		if (data->err_acc <= data->err_temp)
			start->x += data->slope;
		start->y++;
		data->colour = avg_colour(start->colour, end->colour, \
					data->dy, data->save);
		win->set_pixel(win, start->x, start->y, \
			gamma_average(win->get_pixel(win, start->x, \
			start->y), data->colour, (float)data->err_acc / (float)USHRT_MAX));
		win->set_pixel(win, start->x + data->slope, start->y, gamma_average \
			(win->get_pixel(win, start->x + data->slope, start->y), \
			data->colour, (float)(USHRT_MAX - data->err_acc) \
			/ (float)USHRT_MAX));
	}
	win->set_pixel(win, end->x, end->y, end->colour);
	return (1);
}
