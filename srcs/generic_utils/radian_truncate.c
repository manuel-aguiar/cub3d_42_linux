/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radian_truncate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:22:11 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 16:22:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_utils.h"

float	radian_truncate(float radian)
{
	if (radian >= 2 * P_MY_PI)
		return (0 + (float)(radian - 2 * P_MY_PI));
	if (radian < -2 * P_MY_PI)
		return (0 + (float)(radian + 2 * P_MY_PI));
	return (radian);
}
