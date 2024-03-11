/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_east.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:44:47 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:44:47 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

void	init_template_east(t_compass *comp)
{
	comp->east[E_BOT_LEFT] = (t_pixel){-comp->letter_width / 2 - 1, \
		- (comp->letter_height / 2 + 1), comp->letter_color};
	comp->east[E_BOT_RIGHT] = (t_pixel){(comp->letter_width / 2 + 1), \
		- (comp->letter_height / 2 + 1), comp->letter_color};
	comp->east[E_TOP_LEFT] = (t_pixel){-comp->letter_width / 2 - 1, \
		(comp->letter_height / 2 + 1), comp->letter_color};
	comp->east[E_TOP_RIGHT] = (t_pixel){(comp->letter_width / 2 + 1), \
		(comp->letter_height / 2 + 1), comp->letter_color};
	comp->east[E_MID_LEFT] = (t_pixel){-comp->letter_width / 2 - 1, \
		0, comp->letter_color};
	comp->east[E_MID_RIGHT] = (t_pixel){(comp->letter_width / 2 + 1), \
		0, comp->letter_color};
}

void	render_east_letter(t_win *win, t_compass *comp)
{
	t_pixel	east[E_SIZE];
	int		i;
	int		dx;
	int		dy;

	ft_memcpy(east, comp->east, sizeof(*east) * E_SIZE);
	dx = comp->centre.x;
	dy = comp->centre.y + comp->letter_radius;
	i = 0;
	while (i < E_SIZE)
	{
		translate_point(&east[i], dx, dy);
		rotate_point(&east[i], comp->centre, comp->cos_rad, -comp->sin_rad);
		i++;
	}
	xiaolinwu_line(win, east[E_BOT_LEFT], east[E_TOP_LEFT]);
	xiaolinwu_line(win, east[E_TOP_LEFT], east[E_TOP_RIGHT]);
	xiaolinwu_line(win, east[E_BOT_LEFT], east[E_BOT_RIGHT]);
	xiaolinwu_line(win, east[E_MID_LEFT], east[E_MID_RIGHT]);
}
