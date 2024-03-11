/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:43:47 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:43:47 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

void	translate_compass(t_compass *comp, int dx, int dy)
{
	comp->centre.x += dx;
	comp->centre.y += dy;
}

float	normal_distribution(float x, float sigma)
{
	return (exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * MY_PI) * sigma));
}

void	setup_blur_kernel(t_comp_blur *blur)
{
	int		i;
	float	sum;

	blur->centre = blur->kernel_size / 2;
	sum = 0;
	i = 0;
	while (i < blur->kernel_size)
	{
		blur->kernel[i] = normal_distribution(i - blur->centre, blur->sigma);
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

int	compass_blur_setup(t_compass *comp)
{
	t_comp_blur	*blur;

	blur = &comp->blur;
	if (blur->kernel_size > blur->max_kernel || blur->kernel_size % 2 == 0)
		return (0);
	blur->blur_height = (comp->radius * 2 + 1);
	blur->hori_blur = malloc(sizeof(*blur->hori_blur) \
		* (blur->blur_height * blur->blur_height));
	blur->verti_blur = malloc(sizeof(*blur->verti_blur) \
		* (blur->blur_height * blur->blur_height));
	if (!blur->hori_blur || !blur->verti_blur)
		return (perror_msg_int("malloc", 0));
	blur->rad_diff = comp->radius - comp->inner.radius;
	blur->img_x = (comp->centre.x - comp->radius);
	blur->img_y = (comp->centre.y - comp->radius);
	setup_blur_kernel(blur);
	return (1);
}

int	compass_setup(t_compass *comp)
{
	init_template_north(comp);
	init_template_south(comp);
	init_template_east(comp);
	init_template_west(comp);
	if (!init_template_square(comp) \
	|| !init_inner_circle(comp) \
	|| !compass_blur_setup(comp))
		return (0);
	return (1);
}
