/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:51:20 by marvin            #+#    #+#             */
/*   Updated: 2024/01/17 11:51:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

float normal_distribution(float x, float sigma)
{
    return (exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * MY_PI) * sigma));
}

void setup_blur_kernel(t_blur *blur)
{
	int 	centre;
	int 	i;
	float 	sum;

	centre = blur->kernel_size / 2;
	sum = 0;

	i = 0;
	while (i < blur->kernel_size)
	{
        blur->kernel[i] = normal_distribution(i - centre, blur->sigma);
        sum += blur->kernel[i];	
		i++;	
	}
	i = 0;
	while (i < blur->kernel_size)
	{
		blur->kernel[i] /= sum;
		i++;
	}
}

int		compass_blur_setup(t_compass *comp)
{
	t_blur *blur;

	blur = &comp->blur;
	
	if (blur->kernel_size > blur->max_kernel ||  blur->kernel_size % 2 == 0)
		return (0);
	blur->blur_height = (comp->radius * 2 + 1);
	blur->hori_blur = malloc(sizeof(*blur->hori_blur) * (blur->blur_height * blur->blur_height));
	blur->verti_blur = malloc(sizeof(*blur->verti_blur) * (blur->blur_height * blur->blur_height));
	if (!blur->hori_blur || !blur->verti_blur)
		return (perror_msg_int("malloc",0));
	setup_blur_kernel(blur);
	return (1);
}


int		compass_setup(t_compass *comp)
{
	init_template_north(comp);
	init_template_south(comp);
	init_template_east(comp);
	init_template_west(comp);
	if(!init_template_square(comp)
	|| !init_inner_circle(comp)
	|| !compass_blur_setup(comp))
		return (0);
	return (1);
}

void	translate_compass(t_compass *comp, int dx, int dy)
{
	comp->centre.x += dx;
	comp->centre.y += dy;
}

void	render_compass(t_win *win, t_compass *comp)
{

	//t_pixel c_comp = {400, 400, rgba(255,255,255,255)};
//
	//render_full_circle_with_aa(win, c_comp, comp->radius, rgba(0,255,0,255));
	
	if (comp->blur_on)
		blur_compass(win, comp);
	
	draw_ring_to_inner_circle(win, comp);
	

	render_north_letter(win, comp);
	render_south_letter(win, comp);
	render_east_letter(win, comp);
	render_west_letter(win, comp);
}

void		free_compass(t_compass *comp)
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
