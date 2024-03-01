/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:27:45 by marvin            #+#    #+#             */
/*   Updated: 2024/02/09 19:27:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

//too distance return 0, can use to reduce rendering times of floor and ceiling and even walls

int	add_shade(int color, float perc)
{
	if (perc > 1)
		return (0);
	return (rgba((int)(rgb_r(color) * ( 1 - perc)), \
	(int)(rgb_g(color) * ( 1 - perc)), \
	(int)(rgb_b(color) * ( 1 - perc)), \
	rgb_a(color)));
}

int	add_shade_new(int color, float perc)
{
	char	*pixels;

	
	if (perc > 1)
		return (0);
	pixels = (char *)&color;
	pixels[0] = (char)(pixels[0] * ( 1 - perc));
	pixels[1] = (char)(pixels[1] * ( 1 - perc));
	pixels[2] = (char)(pixels[2] * ( 1 - perc));
	pixels[3] = 255;
	//pixels[3] = (char)(pixels[3] * ( 1 - perc));
	return (color);
}