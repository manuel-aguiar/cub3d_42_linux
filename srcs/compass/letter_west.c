/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_west.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:45:01 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:45:01 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

void	init_template_west(t_compass *comp)
{
	comp->west[W_TOP_LEFT] = (t_pixel){-comp->letter_width - 1, \
		(comp->letter_height / 2 + 1), comp->letter_color};
	comp->west[W_MB_LEFT] = (t_pixel){-comp->letter_width / 2, \
		-(comp->letter_height / 2 + 1), comp->letter_color};
	comp->west[W_TOP_MID] = (t_pixel){0, (comp->letter_height / 2 + 1), \
		comp->letter_color};
	comp->west[W_MB_RIGHT] = (t_pixel){(comp->letter_width / 2), \
		-(comp->letter_height / 2 + 1), comp->letter_color};
	comp->west[W_TOP_RIGHT] = (t_pixel){(comp->letter_width + 1), \
		(comp->letter_height / 2 + 1), comp->letter_color};
}

void	render_west_letter(t_win *win, t_compass *comp)
{
	t_pixel	west[W_SIZE];
	int		i;
	int		dx;
	int		dy;

	ft_memcpy(west, comp->west, sizeof(*west) * W_SIZE);
	dx = comp->centre.x;
	dy = comp->centre.y + comp->letter_radius;
	i = 0;
	while (i < W_SIZE)
	{
		translate_point(&west[i], dx, dy);
		rotate_point(&west[i], comp->centre, -comp->cos_rad, comp->sin_rad);
		i++;
	}
	xiaolinwu_line(win, west[W_TOP_LEFT], west[W_MB_LEFT]);
	xiaolinwu_line(win, west[W_MB_LEFT], west[W_TOP_MID]);
	xiaolinwu_line(win, west[W_TOP_MID], west[W_MB_RIGHT]);
	xiaolinwu_line(win, west[W_MB_RIGHT], west[W_TOP_RIGHT]);
}
