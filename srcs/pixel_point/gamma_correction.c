/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamma_correction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:10:14 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 19:10:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel_point.h"

/*
https://stackoverflow.com/questions/48903716/fast-image-gamma-correction
 replace pow(float x, float 2.2f) with this
it is a polinomial aproximation for the function x^2.2 when 0 < x < 1
*/

float	gamma22_pow(float x)
{
	return (0.8 * x * x + 0.2 * x * x * x);
}

/*
https://mimosa-pudica.net/fast-gamma/
 polynomial aproximation for inversegamma. x ^ (1.0 / 2.2f)
 using quake fast inverse square root for values between 0 and 1 (this case)
 symetrical to x ^ 2.2f around y = x;
 0.8 * x ^ 1 / 2 + 0.2 * x ^ 1 / 3
 equally bad, one square root and on cube root
 (1.138 / x ^ 0.5 - 0.138) * x, good aprox and gets rid of the cube root
*/

float	inverse_gamma22_pow(float x)
{
	return ((1.138f / sqrt(x) - 0.138f) * x);
}

int	gamma_average(int start, int end, float perc_start)
{
	t_gamma_avg	g;

	g.start_weight = perc_start;
	g.end_weight = 1.0f - perc_start;
	g.r_blend = inverse_gamma22_pow(gamma22_pow(rgb_r(start) / 255.0f) \
		* g.start_weight + gamma22_pow(rgb_r(end) / 255.0f) * g.end_weight);
	g.g_blend = inverse_gamma22_pow(gamma22_pow(rgb_g(start) / 255.0f) \
		* g.start_weight + gamma22_pow(rgb_g(end) / 255.0f) * g.end_weight);
	g.b_blend = inverse_gamma22_pow(gamma22_pow(rgb_b(start) / 255.0f) \
		* g.start_weight + gamma22_pow(rgb_b(end) / 255.0f) * g.end_weight);
	g.r_final = (t_uchar)(g.r_blend * 255.0f);
	g.g_final = (t_uchar)(g.g_blend * 255.0f);
	g.b_final = (t_uchar)(g.b_blend * 255.0f);
	return (rgba(g.r_final, g.g_final, g.b_final, 255));
}
