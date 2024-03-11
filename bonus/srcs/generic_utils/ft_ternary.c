/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_ternary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:30:33 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 14:30:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_utils.h"

float	float_ternary(bool cond, float yes, float no)
{
	if (cond)
		return (yes);
	return (no);
}

void	*ptr_ternary(bool cond, void *yes, void *no)
{
	if (cond)
		return (yes);
	return (no);
}
