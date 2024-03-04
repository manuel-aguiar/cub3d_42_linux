/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_equal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:28:47 by marvin            #+#    #+#             */
/*   Updated: 2024/03/04 15:30:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_utils.h"

bool	float_equal(float num, float target, float error)
{
	if (ft_fabs(num - target) <= error)
		return (1);
	return (0);
}
