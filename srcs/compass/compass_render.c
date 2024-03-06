/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:44:24 by codespace         #+#    #+#             */
/*   Updated: 2024/03/06 14:44:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

void	render_compass(t_win *win, t_compass *comp)
{
	if (comp->blur_on)
		blur_compass(win, comp);
	draw_ring_to_inner_circle(win, comp);
	render_north_letter(win, comp);
	render_south_letter(win, comp);
	render_east_letter(win, comp);
	render_west_letter(win, comp);
}

void	free_compass(t_compass *comp)
{
	if (comp->sqr_x_lim)
		free(comp->sqr_x_lim);
	if (comp->circle_x_lim)
		free(comp->circle_x_lim);
	if (comp->blur.hori_blur)
		free(comp->blur.hori_blur);
	if (comp->blur.verti_blur)
		free(comp->blur.verti_blur);
}
