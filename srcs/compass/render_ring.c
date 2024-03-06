/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:48:21 by marvin            #+#    #+#             */
/*   Updated: 2024/01/21 11:48:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

void	drop_the_blur(t_win *win, t_compass *comp, t_hori_line *draw)
{
	t_comp_blur	*blur;
	int			blur_y;
	int			blur_x;

	if (!comp->blur_on)
		return ;
	blur = &comp->blur;
	blur_y = comp->radius + draw->y - comp->centre.y;
	blur_x = comp->radius + draw->min_x - comp->centre.x;
	while (draw->min_x < draw->max_x)
	{
		blur_x = comp->radius + draw->min_x - comp->centre.x;
		win->set_pixel(win, draw->min_x++, draw->y, \
			blur->verti_blur[blur_y * blur->blur_height + blur_x]);
	}
}


void setpixel_inner(t_win *win, t_compass *comp, int c_min_max[MM_SIZE], \
int centreX, int centreY, int deltaX, int deltaY, int color, float perc_start, bool line)
{
	t_hori_line	draw;
	int			index;

    win->set_pixel(win, centreX + deltaX, centreY + deltaY, gamma_average(win->get_pixel(win, centreX + deltaX, centreY + deltaY), color, perc_start));
    win->set_pixel(win, centreX - deltaX, centreY + deltaY, gamma_average(win->get_pixel(win, centreX - deltaX, centreY + deltaY), color, perc_start));

    win->set_pixel(win, centreX + deltaX, centreY - deltaY, gamma_average(win->get_pixel(win, centreX + deltaX, centreY - deltaY), color, perc_start));
    win->set_pixel(win, centreX - deltaX, centreY - deltaY, gamma_average(win->get_pixel(win, centreX - deltaX, centreY - deltaY), color, perc_start));
	draw.color = color;
	if (line)
	{
		draw.y = centreY + deltaY;
		if (centreY + deltaY > c_min_max[MM_MAX_Y])
		{
			draw.min_x = centreX - deltaX;
			draw.max_x = centreX + deltaX;

			draw_horizontal_line(win, &draw);
		}
		else
		{

			index = centreY + deltaY - comp->inner.centre.y + comp->inner.radius;

			draw.min_x = centreX - deltaX;
			draw.max_x = comp->circle_x_lim[index].min + comp->inner.centre.x;
			draw_horizontal_line(win, &draw);
			if (comp->blur_on == true)
			{
				draw.min_x = comp->circle_x_lim[index].min + comp->inner.centre.x;
				draw.max_x = comp->circle_x_lim[index].max + comp->inner.centre.x;
				drop_the_blur(win, comp, &draw);
			}
			draw.min_x = comp->circle_x_lim[index].max + comp->inner.centre.x;
			draw.max_x = centreX + deltaX;
			draw_horizontal_line(win, &draw);
		}
		draw.y = centreY - deltaY;
		if (centreY - deltaY < c_min_max[MM_MIN_Y])
		{
			draw.min_x = centreX - deltaX;
			draw.max_x = centreX + deltaX;
			draw_horizontal_line(win, &draw);
		}
		else if (deltaY)	//double rendering the same line
		{

			index = centreY - deltaY - comp->inner.centre.y + comp->inner.radius;
			draw.min_x = centreX - deltaX;
			draw.max_x = comp->circle_x_lim[index].min + comp->inner.centre.x;

			draw_horizontal_line(win, &draw);
			if (comp->blur_on == true)
			{
				draw.min_x = comp->circle_x_lim[index].min + comp->inner.centre.x;
				draw.max_x = comp->circle_x_lim[index].max + comp->inner.centre.x;
				drop_the_blur(win, comp, &draw);

			}
			draw.min_x = comp->circle_x_lim[index].max + comp->inner.centre.x;
			draw.max_x = centreX + deltaX;
			draw_horizontal_line(win, &draw);
		}
	}
}

void draw_ring_to_inner_circle(t_win *win, t_compass *comp)
{
	t_pixel centre;
	int		radius;
	int		color;
	int		c_min_max[MM_SIZE];

	ft_memcpy(&c_min_max, &comp->inner.min_max, sizeof(c_min_max));
	c_min_max[MM_MIN_X] += comp->centre.x;
	c_min_max[MM_MAX_X] += comp->centre.x;
	c_min_max[MM_MIN_Y] += comp->centre.y;
	c_min_max[MM_MAX_Y] += comp->centre.y;


	centre = comp->centre;
	radius = comp->radius;
	color = comp->color;
	int centreX = centre.x;
	int centreY = centre.y;
    int radius2 = radius * radius;

    // Upper and lower halves
    int quarter = round(radius2 / sqrt(radius2 + radius2));
    for (int x = 0; x <= quarter; x++) {
        float y = radius * sqrt(1 - x * x / (float)radius2);
        float error = y - (int)(y);

        setpixel_inner(win, comp, c_min_max, centreX, centreY, x, (int)(y), color, error, true);
		setpixel_inner(win, comp, c_min_max, centreX, centreY, (int)(y), x, color, error, true);
        setpixel_inner(win, comp, c_min_max, centreX, centreY, x, (int)(y) + 1, color, 1 - error, false);
		setpixel_inner(win, comp, c_min_max, centreX, centreY, (int)(y) + 1, x, color, 1 - error, false);
    }

}
