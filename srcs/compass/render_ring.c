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

# include "compass.h"

/*Midpoint Circle algorithm, by calculating 1/8 of a circle, one can render the
full object by projecting coordinates

i will have to use a hashtable to store the circles coordinates to make collision
detection easier. inner circle will not be moveable so the coordinates will always
be valid. if the circle has atmost 200 height, i'll be storing 1600 bytes,
so it is a very small table and not drain much memory

hashtable for the square as well, for each single frame the square will be the same for everyone except
the offset from where it starts off, with a couple of lookups i can check the boundaries for
each scanline and print only what is needed

*/

// must be visible

// gamma correction instead of linear average of pixels when antialiasing



// turn these into hash tables...? the inverse pow becoming 2 sqrrts.....

//quake fast inverse square root of doom


void setPixel4(t_win *win, int centreX, int centreY, int deltaX, int deltaY, int color, float perc_start, bool line)
{
	t_hori_line	draw;

    win->set_pixel(win, centreX + deltaX, centreY + deltaY, gamma_average(win->get_pixel(win, centreX + deltaX, centreY + deltaY), color, perc_start));
    win->set_pixel(win, centreX - deltaX, centreY + deltaY, gamma_average(win->get_pixel(win, centreX - deltaX, centreY + deltaY), color, perc_start));

    win->set_pixel(win, centreX + deltaX, centreY - deltaY, gamma_average(win->get_pixel(win, centreX + deltaX, centreY - deltaY), color, perc_start));
    win->set_pixel(win, centreX - deltaX, centreY - deltaY, gamma_average(win->get_pixel(win, centreX - deltaX, centreY - deltaY), color, perc_start));

	if (line)
	{
		draw.color = color;
		draw.min_x = centreX - deltaX;
		draw.max_x = centreX + deltaX;
		draw.y = centreY + deltaY;
		draw_horizontal_line(win, &draw);
		draw.y = centreY - deltaY;
		draw_horizontal_line(win, &draw);
	}
}

void render_full_circle_with_aa(t_win *win, t_pixel centre, int radius, int color)
{

	int centreX = centre.x;
	int centreY = centre.y;
    int radius2 = radius * radius;

    // Upper and lower halves
    int quarter = round(radius2 / sqrt(radius2 + radius2));
    for (int x = 0; x <= quarter; x++) {
        float y = radius * sqrt(1 - x * x / (float)radius2);
        float error = y - (int)(y);

        setPixel4(win, centreX, centreY, x, (int)(y), color, error, true);
		setPixel4(win, centreX, centreY, (int)(y), x, color, error, true);
        setPixel4(win, centreX, centreY, x, (int)(y) + 1, color, 1.0f - error, false);
		setPixel4(win, centreX, centreY, (int)(y) + 1, x, color, 1.0f - error, false);
    }
}

void render_empty_circle_with_aa(t_win *win, t_pixel centre, int radius, int color)
{
	int centreX = centre.x;
	int centreY = centre.y;
    int radius2 = radius * radius;

    // Upper and lower halves
    int quarter = round(radius2 / sqrt(radius2 + radius2));
    for (int x = 0; x <= quarter; x++) {
        float y = radius * sqrt(1 - x * x / (float)radius2);
        float error = y - (int)(y);

        setPixel4(win, centreX, centreY, x, (int)(y), color, error, false);  //lol
		setPixel4(win, centreX, centreY, (int)(y), x, color, error, false);	 //lol
        setPixel4(win, centreX, centreY, x, (int)(y) + 1, color, 1.0f - error, false);
		setPixel4(win, centreX, centreY, (int)(y) + 1, x, color, 1.0f - error, false);
    }
}


void	reduce_alpha_horizontal_line(t_win *win, int min_x, int max_x, int y, float factor)
{
	int color;

	while (min_x <= max_x)
	{
		//printf("old color: %d, new color %d\n", color, ARGB(RGB_R(color), RGB_G(color), RGB_B(color), (int)(RGB_A(color) * factor)));
		color = win->get_pixel(win, min_x, y);
		win->set_pixel(win, min_x++, y, rgba(rgb_r(color), rgb_g(color), rgb_b(color), (int)(rgb_a(color) * factor)));
	}
}

void	drop_the_blur(t_win *win, t_compass *comp, t_hori_line *draw)
{
	t_blur *blur;
	int blur_y;
	int	blur_x;

	if (!comp->blur_on)
		return ;
	blur = &comp->blur;
	blur_y = comp->radius + draw->y - comp->centre.y;
	blur_x = comp->radius + draw->min_x - comp->centre.x;
	int blur_index = blur->verti_blur[blur_y * blur->blur_height + blur_x];
	int screen_index = (draw->min_x + draw->y * win->width) * win->rgb_size;
	//ft_memcpy(&win->front_buf[screen_index], &blur[blur_index], (max_x - min_x) * sizeof(blur[blur_index]));

	(void)blur_index;
	(void)screen_index;
	// replace with memcpy!!!!
	while (draw->min_x < draw->max_x)
	{
		blur_x = comp->radius + draw->min_x - comp->centre.x;
		win->set_pixel(win, draw->min_x++, draw->y, blur->verti_blur[blur_y * blur->blur_height + blur_x]);
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
