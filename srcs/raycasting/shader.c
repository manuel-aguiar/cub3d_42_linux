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

int	add_shade(int color, float perc)
{
	if (perc > 1)
		return (0);
	return (rgba((int)(rgb_r(color) * (1 - perc)), \
	(int)(rgb_g(color) * (1 - perc)), \
	(int)(rgb_b(color) * (1 - perc)), \
	rgb_a(color)));
}
