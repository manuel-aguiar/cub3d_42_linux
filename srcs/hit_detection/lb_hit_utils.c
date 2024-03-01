/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_lb_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:41:20 by marvin            #+#    #+#             */
/*   Updated: 2023/07/21 14:41:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit_detection.h"

float	lb_hit_maxi(float arr[], int n)
{
	float	m;
	int		i;

	m = 0;
	i = 0;
	while (i < n)
	{
		if (m < arr[i])
			m = arr[i];
		i++;
	}
	return (m);
}

float	lb_hit_mini(float arr[], int n)
{
	float	m;
	int		i;

	m = 1;
	i = 0;
	while (i < n)
	{
		if (m > arr[i])
			m = arr[i];
		i++;
	}
	return (m);
}
