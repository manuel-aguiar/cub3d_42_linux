/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_circle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:25:51 by marvin            #+#    #+#             */
/*   Updated: 2024/01/18 19:25:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void	render_inner_circle(t_win *win, t_compass *comp)
{
	t_circle	*inner;
	int	y_adj;
	int	i;

	inner = &comp->inner;
	i = 0;
	y_adj = inner->min_max[MM_MIN_Y] + inner->centre.y;
	while (i < inner->radius * 2 + 1)
	{
		win->set_pixel(win, comp->circle_x_lim[i].min + inner->centre.x, i + y_adj, inner->color);
		win->set_pixel(win, comp->circle_x_lim[i].max + inner->centre.x, i + y_adj, inner->color);
		i++;
	}
	win->set_pixel(win, inner->centre.x, y_adj, inner->color);
	win->set_pixel(win, inner->centre.x, y_adj, inner->color);
}

void	inner_all_decisions(t_compass *comp, t_circle *inner, int x, int y)
{
		comp->circle_x_lim[y + inner->radius].min = ft_min(comp->circle_x_lim[y + inner->radius].min, x);
		comp->circle_x_lim[y + inner->radius].max = ft_max(comp->circle_x_lim[y + inner->radius].max, x);
}

void	inner_circle_circle_x_lim(t_compass *comp, t_circle *inner)
{
	int x;
	int y;
	int decision;

	x = inner->radius;
	y = 0;
	decision = 1 - inner->radius;
	while (y <= x)
	{
		inner_all_decisions(comp, inner, x, y);
		inner_all_decisions(comp, inner, -x, y);
		inner_all_decisions(comp, inner, x, -y);
		inner_all_decisions(comp, inner, -x, -y);
		inner_all_decisions(comp, inner, y, x);
		inner_all_decisions(comp, inner, -y, x);
		inner_all_decisions(comp, inner, y, -x);
		inner_all_decisions(comp, inner, -y, -x);
		y++;
		if (decision <= 0)
			decision += 2 * y + 1;
		else
		{
			x--;
			decision += 2 * (y - x) + 1;
		}
	}
}

int init_inner_circle(t_compass *comp)
{
	t_circle *inner;
	int      i;

	inner = &comp->inner;
	inner->centre = comp->centre;

	
	comp->circle_x_lim = malloc(sizeof(*comp->circle_x_lim) * (inner->radius * 2 + 1));
	if (!comp->circle_x_lim)
		return (perror_msg_int("malloc",0));				//mallloc failed perror

	inner->min_max[MM_MIN_X] = - inner->radius;
	inner->min_max[MM_MAX_X] = + inner->radius;
	inner->min_max[MM_MIN_Y] = - inner->radius;
	inner->min_max[MM_MAX_Y] = + inner->radius;
	i = 0;
	while (i < inner->radius * 2 + 1)
	{
		comp->circle_x_lim[i].min = INT_MAX;
		comp->circle_x_lim[i].max = INT_MIN;
		i++;
	}
	inner_circle_circle_x_lim(comp, inner);
	return (1);
}