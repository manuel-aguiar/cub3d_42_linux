/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rand_gen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:42:23 by codespace         #+#    #+#             */
/*   Updated: 2024/03/12 20:10:50 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	rand_init(void)
{
	time_t	t;

	srand((unsigned) time(&t));
}

float	rand_float(float min, float max)
{
	float	temp;
	float	res;

	temp = (double)rand() / (double)RAND_MAX;
	res = temp * (max - min) + min;
	return (res);
}

int	rand_int(int min, int max)
{
	int	res;

	res = (rand() % (max - min + 1)) + min;
	return (res);
}
