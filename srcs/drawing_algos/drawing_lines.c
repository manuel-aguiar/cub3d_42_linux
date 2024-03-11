/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:45:19 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:45:19 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing_algos.h"

void	draw_horizontal_line(t_win *win, t_hori_line *data)
{
	while (data->min_x <= data->max_x)
		win->set_pixel(win, data->min_x++, data->y, data->color);
}

void	draw_vertical_line(t_win *win, t_verti_line *data)
{
	while (data->min_y <= data->max_y)
		win->set_pixel(win, data->x, data->min_y++, data->color);
}

static inline void
	bersenham_line_setup(t_bh_line *bh, t_pixel start, t_pixel end)
{
	bh->x1 = start.x;
	bh->y1 = start.y;
	bh->x2 = end.x;
	bh->y2 = end.y;
	bh->dx = ft_abs(bh->x2 - bh->x1);
	bh->dy = ft_abs(bh->y2 - bh->y1);
	bh->sx = ft_ternary(bh->x1 < bh->x2, 1, -1);
	bh->sy = ft_ternary(bh->y1 < bh->y2, 1, -1);
	bh->err = bh->dx - bh->dy;
}

void	bersenham_line(t_win *win, t_pixel start, t_pixel end, int color)
{
	t_bh_line	bh;

	bersenham_line_setup(&bh, start, end);
	while (1)
	{
		win->set_pixel(win, bh.x1, bh.y1, color);
		if (bh.x1 == bh.x2 && bh.y1 == bh.y2)
			break ;
		bh.err_2 = 2 * bh.err;
		if (bh.err_2 > -bh.dy)
		{
			bh.err -= bh.dy;
			bh.x1 += bh.sx;
		}
		if (bh.err_2 < bh.dx)
		{
			bh.err += bh.dx;
			bh.y1 += bh.sy;
		}
	}
}
