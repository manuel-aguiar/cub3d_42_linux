/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:33:48 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 16:33:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	int_clamp(int value, int min, int max)
{
	return (ft_min(max, ft_max(min, value)));
}

float	float_clamp(float value, float min, float max)
{
	return (ft_fmin(max, ft_fmax(min, value)));
}
