/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_north.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:49 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 13:51:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void	init_template_north(t_compass *comp)
{
	comp->north[N_BOT_LEFT] = (t_pixel){-(comp->letter_width / 2 + 1), \
		-(comp->letter_height / 2 + 1), comp->letter_color};
	comp->north[N_BOT_RIGHT] = (t_pixel){+(comp->letter_width / 2 + 1), \
		-(comp->letter_height / 2 + 1), comp->letter_color};
	comp->north[N_TOP_LEFT] = (t_pixel){-(comp->letter_width / 2 + 1), \
		+(comp->letter_height / 2 + 1), comp->letter_color};
	comp->north[N_TOP_RIGHT] = (t_pixel){+(comp->letter_width / 2 + 1), \
		+(comp->letter_height / 2 + 1), comp->letter_color};
}

void	render_north_letter(t_win *win, t_compass *comp)
{
	t_pixel	north[N_SIZE];
	int		i;
	int		dx;
	int		dy;

	ft_memcpy(north, comp->north, sizeof(*north) * N_SIZE);
	dx = comp->centre.x;
	dy = comp->centre.y + comp->letter_radius;
	i = 0;
	while (i < N_SIZE)
	{
		translate_point(&north[i], dx, dy);
		north[i].colour = 255 << 16;
		rotate_point(&north[i], comp->centre, -comp->sin_rad, -comp->cos_rad);
		i++;
	}
	xiaolinwu_line(win, north[N_BOT_LEFT], north[N_TOP_LEFT]);
	xiaolinwu_line(win, north[N_TOP_LEFT], north[N_BOT_RIGHT]);
	xiaolinwu_line(win, north[N_BOT_RIGHT], north[N_TOP_RIGHT]);
}
