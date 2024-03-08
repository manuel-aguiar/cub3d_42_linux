/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:26:48 by codespace         #+#    #+#             */
/*   Updated: 2024/03/06 12:28:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel_point.h"

int	argb(int color)
{
	int	new;

	new = ((color & 0xff) << 24) \
	| (((color >> 8) & 0xff) << 16) \
	| (((color >> 16) & 0xff) << 8) \
	| ((color >> 24) & 0xff);
	return (new);
}

int	abgr_inversion(int r, int g, int b, int a)
{
	return ((a << 24) | (b << 16) | (g << 8) | (r));
}

int	pack_color_channels(int fst, int snd, int trd, int fth)
{
	return ((fst << 24) | (snd << 16) | (trd << 8) | (fth));
}

int	avg_colour(int start, int end, int num, int den)
{
	t_ulong	r;
	t_ulong	g;
	t_ulong	b;

	if (den == 0)
		return (start);
	r = ((start >> 16) & 0xff) * num / den \
		+ ((end >> 16) & 0xff) * (den - num) / den;
	g = ((start >> 8) & 0xff) * num / den \
		+ ((end >> 8) & 0xff) * (den - num) / den;
	b = (start & 0xff) * num / den \
		+ (end & 0xff) * (den - num) / den;
	return (((((int)r) << 16) | (((int)g) << 8) | ((int)b)));
}
