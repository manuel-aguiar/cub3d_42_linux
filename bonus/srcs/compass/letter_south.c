/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_south.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:44:57 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:44:57 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

void	init_template_south(t_compass *comp)
{
	comp->south[S_BOT_LEFT] = (t_pixel){-comp->letter_width / 2 - 1, \
		- (comp->letter_height / 2 + 1), comp->letter_color};
	comp->south[S_BOT_RIGHT] = (t_pixel){(comp->letter_width / 2 + 1), \
		- (comp->letter_height / 2 + 1), comp->letter_color};
	comp->south[S_TOP_LEFT] = (t_pixel){-comp->letter_width / 2 - 1, \
		(comp->letter_height / 2 + 1), comp->letter_color};
	comp->south[S_TOP_RIGHT] = (t_pixel){(comp->letter_width / 2 + 1), \
		(comp->letter_height / 2 + 1), comp->letter_color};
	comp->south[S_MID_LEFT] = (t_pixel){-comp->letter_width / 2 - 1, \
		0, comp->letter_color};
	comp->south[S_MID_RIGHT] = (t_pixel){(comp->letter_width / 2 + 1), \
		0, comp->letter_color};
}

void	render_south_letter(t_win *win, t_compass *comp)
{
	t_pixel	south[S_SIZE];
	int		i;
	int		dx;
	int		dy;

	ft_memcpy(south, comp->south, sizeof(*south) * S_SIZE);
	dx = comp->centre.x;
	dy = comp->centre.y + comp->letter_radius;
	i = 0;
	while (i < S_SIZE)
	{
		translate_point(&south[i], dx, dy);
		rotate_point(&south[i], comp->centre, comp->sin_rad, comp->cos_rad);
		i++;
	}
	xiaolinwu_line(win, south[S_BOT_LEFT], south[S_BOT_RIGHT]);
	xiaolinwu_line(win, south[S_BOT_RIGHT], south[S_MID_RIGHT]);
	xiaolinwu_line(win, south[S_MID_RIGHT], south[S_MID_LEFT]);
	xiaolinwu_line(win, south[S_MID_LEFT], south[S_TOP_LEFT]);
	xiaolinwu_line(win, south[S_TOP_LEFT], south[S_TOP_RIGHT]);
}
