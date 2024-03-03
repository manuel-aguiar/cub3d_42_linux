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

# include "game.h"


void	xpm_to_window(t_win *win, t_xpm_tex *tex, t_pixel bot_left, int pixel_wdt, int pixel_hgt)
{
	if (bot_left.x + pixel_wdt > win->width || bot_left.y + pixel_hgt > win->height)
		return ;
	
	int i;
	int j;
	int row;
	int column;

	i = pixel_hgt - 1;
	while (i >= 0)
	{
		row = (int)((pixel_hgt - i - 1) * ((float)tex->height / (float)pixel_hgt));
		j = 0;
		while (j < pixel_wdt)
		{
			column = (int)(j * ((float)tex->width / (float)pixel_wdt));
			//printf("i %d j %d, row %d col %d, pixel val is %d\n",i, j, row, column, tex->pixels[column + row * tex->width]);
			int color = tex->pixels[column + row * tex->width];
			if (color != 0)
				win->set_pixel(win, bot_left.x + j, bot_left.y + i, tex->pixels[column + row * tex->width]);
			j++;
		}
		i--;
	}
}