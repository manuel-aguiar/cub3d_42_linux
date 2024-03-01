/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:04:16 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 19:04:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing_algos.h"

void	draw_horizontal_line(t_win *win, int min_x, int max_x, int y, int color)
{
	while (min_x <= max_x)
		win->set_pixel(win, min_x++, y, color);
}

void	draw_vertical_line(t_win *win, int start_y, int end_y, int x, int color)
{
	while (start_y <= end_y)
		win->set_pixel(win, x, start_y++, color);
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
