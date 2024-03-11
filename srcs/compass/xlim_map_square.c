/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xlim_map_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:45:14 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:45:14 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

void	bersenham_sqr_x_lim(t_compass *comp, t_square *sqr, \
						t_pixel start, t_pixel end);

static void	get_square_edges(t_square *sqr)
{
	int	i;

	sqr->min_max[MM_MIN_X] = sqr->edges[0].x;
	sqr->min_max[MM_MAX_X] = sqr->edges[0].x;
	sqr->min_max[MM_MIN_Y] = sqr->edges[0].y;
	sqr->min_max[MM_MAX_Y] = sqr->edges[0].y;
	i = 1;
	while (i < SQR_SIZE)
	{
		sqr->min_max[MM_MIN_X] \
			= ft_min(sqr->min_max[MM_MIN_X], sqr->edges[i].x);
		sqr->min_max[MM_MAX_X] \
			= ft_max(sqr->min_max[MM_MAX_X], sqr->edges[i].x);
		sqr->min_max[MM_MIN_Y] \
			= ft_min(sqr->min_max[MM_MIN_Y], sqr->edges[i].y);
		sqr->min_max[MM_MAX_Y] \
			= ft_max(sqr->min_max[MM_MAX_Y], sqr->edges[i].y);
		i++;
	}
}

void	calculate_sqr_x_lim(t_compass *comp, t_square *sqr)
{
	int	i;

	get_square_edges(sqr);
	sqr->real_z = sqr->min_max[MM_MAX_Y] - sqr->min_max[MM_MIN_Y] + 1;
	i = 0;
	while (i < sqr->real_z)
	{
		comp->sqr_x_lim[i].min = INT_MAX;
		comp->sqr_x_lim[i].max = INT_MIN;
		i++;
	}
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_BOT_LEFT], \
		sqr->edges[SQR_TOP_LEFT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_TOP_LEFT], \
		sqr->edges[SQR_TOP_RIGHT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_TOP_RIGHT], \
		sqr->edges[SQR_BOT_RIGHT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_BOT_RIGHT], \
		sqr->edges[SQR_BOT_LEFT]);
}

void	compass_square_xlim_rotate(t_compass *comp, t_square *sqr)
{
	int	i;

	sqr->edges[SQR_BOT_LEFT] = (t_pixel){-sqr->height / 2 + 1, \
		- sqr->height / 2 + 1, sqr->color};
	sqr->edges[SQR_TOP_LEFT] = (t_pixel){-sqr->height / 2 + 1, \
		+ sqr->height / 2 - 1, sqr->color};
	sqr->edges[SQR_TOP_RIGHT] = (t_pixel){+sqr->height / 2 - 1, \
		+ sqr->height / 2 - 1, sqr->color};
	sqr->edges[SQR_BOT_RIGHT] = (t_pixel){+sqr->height / 2 - 1, \
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
