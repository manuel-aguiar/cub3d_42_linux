/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xlim_map_square_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:12:12 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 13:41:03 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

static inline void	bersenham_line_setup(t_bh_line *bh, \
					t_pixel start, t_pixel end)
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

void	bersenham_sqr_x_lim(t_compass *comp, t_square *sqr, \
						t_pixel start, t_pixel end)
{
	t_bh_line	bh;
	int			table_y;

	bersenham_line_setup(&bh, start, end);
	while (1)
	{
		table_y = bh.y1 - sqr->min_max[MM_MIN_Y];
		comp->sqr_x_lim[table_y].min = \
			ft_min(comp->sqr_x_lim[table_y].min, bh.x1);
		comp->sqr_x_lim[table_y].max = \
			ft_max(comp->sqr_x_lim[table_y].max, bh.x1);
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
