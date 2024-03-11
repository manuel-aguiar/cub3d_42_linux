/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radian_truncate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:43:01 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:43:01 by mmaria-d         ###   ########.fr       */
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
