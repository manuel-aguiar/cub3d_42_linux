/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rand_gen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:42:23 by codespace         #+#    #+#             */
/*   Updated: 2024/03/05 13:55:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

float	rand_float(t_rand_gen *rand, float min, float max)
{
	float	temp;
	float	res;

	rand->seed += rand->clock->start.tv_sec;
	rand->seed = (rand->seed * rand->multiplier + rand->increment) / RAND_MAX_UINT64;
	temp = (float)rand->seed / (float)RAND_MAX_UINT64;
	res = temp * (max - min) + min;
	return (res);
}

int		rand_int(t_rand_gen *rand, int min, int max)
{
	int	res;

	rand->seed += rand->clock->start.tv_sec;
	rand->seed = (rand->seed * rand->multiplier + rand->increment) / RAND_MAX_UINT64;
	res = (rand->seed % (max - min + 1)) + min;
	return (res);
}
