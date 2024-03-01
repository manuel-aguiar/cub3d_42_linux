/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:12:39 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 16:12:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

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

void bersenham_sqr_x_lim(t_compass *comp, t_square *sqr, \
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
			break;
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


void	calculate_sqr_x_lim(t_compass *comp, t_square *sqr)
{
	int i;

	sqr->min_max[MM_MIN_X] = sqr->edges[0].x;
	sqr->min_max[MM_MAX_X] = sqr->edges[0].x;	
	sqr->min_max[MM_MIN_Y] = sqr->edges[0].y;
	sqr->min_max[MM_MAX_Y] = sqr->edges[0].y;
	i = 1;
	while (i < SQR_SIZE)
	{
		sqr->min_max[MM_MIN_X] = ft_min(sqr->min_max[MM_MIN_X], sqr->edges[i].x);
		sqr->min_max[MM_MAX_X] = ft_max(sqr->min_max[MM_MAX_X], sqr->edges[i].x);
		sqr->min_max[MM_MIN_Y] = ft_min(sqr->min_max[MM_MIN_Y], sqr->edges[i].y);
		sqr->min_max[MM_MAX_Y] = ft_max(sqr->min_max[MM_MAX_Y], sqr->edges[i].y);
		i++;
	}
	sqr->real_z = sqr->min_max[MM_MAX_Y] - sqr->min_max[MM_MIN_Y] + 1;
	i = 0;
	while (i < sqr->real_z)
	{
		comp->sqr_x_lim[i].min = INT_MAX;
		comp->sqr_x_lim[i].max = INT_MIN;
		i++;
	}

	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_BOT_LEFT], sqr->edges[SQR_TOP_LEFT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_TOP_LEFT], sqr->edges[SQR_TOP_RIGHT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_TOP_RIGHT], sqr->edges[SQR_BOT_RIGHT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_BOT_RIGHT], sqr->edges[SQR_BOT_LEFT]);
	
}

void	compass_square_xlim_rotate(t_compass *comp, t_square *sqr)
{
	int	i;

	sqr->edges[SQR_BOT_LEFT] = (t_pixel){- sqr->height / 2 + 1, \
		- sqr->height / 2 + 1, sqr->color};
	sqr->edges[SQR_TOP_LEFT] = (t_pixel){- sqr->height / 2 + 1, \
		+ sqr->height / 2 - 1, sqr->color};
	sqr->edges[SQR_TOP_RIGHT] = (t_pixel){+ sqr->height / 2 - 1, \
		+ sqr->height / 2 - 1, sqr->color};
	sqr->edges[SQR_BOT_RIGHT] = (t_pixel){+ sqr->height / 2 - 1, \
		- sqr->height / 2 + 1, sqr->color};
	i = 0;
	while (i < SQR_SIZE)
	{
		rotate_point(&sqr->edges[i], sqr->centre, \
			-comp->cos_rad, comp->sin_rad);
		i++;
	}
	calculate_sqr_x_lim(comp, sqr);
}

int	init_template_square(t_compass *comp)
{
	t_square	*sqr;

	sqr = &comp->sqr;
	comp->sqr_x_lim = malloc(sizeof(*comp->sqr_x_lim) * sqr->biggest_z);
	if (!comp->sqr_x_lim)
		return (perror_msg_int("malloc", 0));	
	compass_square_xlim_rotate(comp, sqr);
	return (1);
}

