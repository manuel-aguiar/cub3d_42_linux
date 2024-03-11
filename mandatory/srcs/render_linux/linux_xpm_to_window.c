/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:50:10 by marvin            #+#    #+#             */
/*   Updated: 2024/02/05 12:50:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	setup_edges(t_win *win, t_xpm_to_win *xpm)
{
	xpm->start_x = ft_max(xpm->win_low_x, 0);
	xpm->end_x = ft_min(xpm->start_x + xpm->pix_width, win->width - 1);
	xpm->start_y = ft_max(xpm->win_low_y, 0);
	xpm->end_y = ft_min(xpm->start_y + xpm->pix_height, win->height - 1);
}

static inline void	draw_this_line(t_win *win, t_xpm_to_win *xpm, int y)
{
	int	x;
	int	tex_row;
	int	tex_col;

	tex_row = (int)((xpm->pix_height - y - 1) \
	* ((float)xpm->tex->height / (float)xpm->pix_height));
	x = xpm->start_x;
	while (x <= xpm->end_x)
	{
		tex_col = (int)(x * ((float)xpm->tex->width / (float)xpm->pix_width));
		xpm->this_color = tex_get_pixel(win, xpm->tex, \
			tex_col + tex_row * xpm->tex->width);
		if (xpm->this_color != 0)
			win->set_pixel(win, x, y, xpm->this_color);
		x++;
	}
}

void	xpm_to_window(t_win *win, t_xpm_to_win	*xpm)
{
	int	y;

	if (xpm->win_low_x > win->width || xpm->win_low_y > win->height \
	|| xpm->win_low_x + xpm->pix_width < 0 \
	|| xpm->win_low_y + xpm->pix_height < 0)
		return ;
	setup_edges(win, xpm);
	y = xpm->end_y;
	while (y >= xpm->start_y)
	{
		draw_this_line(win, xpm, y);
		y--;
	}
}
