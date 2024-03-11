/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_square.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:45:05 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:45:05 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

static int	circlelim_setup_and_compare(t_compass *comp, t_square *sqr, \
			int c_min_max[MM_SIZE])
{
	ft_memcpy(c_min_max, &comp->inner.min_max, sizeof(c_min_max[0]) * MM_SIZE);
	c_min_max[MM_MIN_X] += comp->centre.x;
	c_min_max[MM_MAX_X] += comp->centre.x;
	c_min_max[MM_MIN_Y] += comp->centre.y;
	c_min_max[MM_MAX_Y] += comp->centre.y;
	if (sqr->min_max[MM_MIN_X] > c_min_max[MM_MAX_X] \
	|| sqr->min_max[MM_MAX_X] < c_min_max[MM_MIN_X] \
	|| sqr->min_max[MM_MIN_Y] > c_min_max[MM_MAX_Y] \
	|| sqr->min_max[MM_MAX_Y] < c_min_max[MM_MIN_Y])
		return (0);
	return (1);
}

static void	square_setup_edges(t_square *sqr, int x, int y)
{
	int	i;

	i = 0;
	while (i < SQR_SIZE)
	{
		translate_point(&sqr->edges[i], x, y);
		i++;
	}
	sqr->min_max[MM_MIN_X] += x;
	sqr->min_max[MM_MAX_X] += x;
	sqr->min_max[MM_MIN_Y] += y;
	sqr->min_max[MM_MAX_Y] += y;
}

void	render_square_vs_circle(t_win *win, t_compass *comp, t_pixel centre)
{
	int				i;
	t_render_sqr	ren;

	ren.sqr = comp->sqr;
	ren.x = centre.x;
	ren.y = centre.y;
	square_setup_edges(&ren.sqr, ren.x, ren.y);
	if (!circlelim_setup_and_compare(comp, &ren.sqr, ren.c_min_max))
		return ;
	i = ft_max(ren.c_min_max[MM_MIN_Y] - ren.sqr.min_max[MM_MIN_Y], 0);
	ren.end = ft_max(ren.sqr.min_max[MM_MAX_Y] - ren.c_min_max[MM_MAX_Y], 0);
	ren.adj_x = ren.sqr.min_max[MM_MIN_Y] - comp->inner.centre.y \
		+ comp->inner.radius;
	while (i < ren.sqr.real_z - ren.end)
	{
		ren.line.min_x = ft_max(comp->sqr_x_lim[i].min + ren.x, \
			comp->circle_x_lim[i + ren.adj_x].min + comp->inner.centre.x);
		ren.line.max_x = ft_min(comp->sqr_x_lim[i].max + ren.x, \
			comp->circle_x_lim[i + ren.adj_x].max + comp->inner.centre.x);
		ren.line.y = i + ren.sqr.min_max[MM_MIN_Y];
		ren.line.color = comp->sqr.color;
		draw_horizontal_line(win, &ren.line);
		i++;
	}
}
