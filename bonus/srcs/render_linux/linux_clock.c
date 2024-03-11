/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_timer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:14:18 by marvin            #+#    #+#             */
/*   Updated: 2024/02/09 19:14:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_linux.h"

void	start_clock(t_clock *clock)
{
	gettimeofday(&clock->start, NULL);
}

void	update_clock(t_clock *clock)
{
	gettimeofday(&clock->end, NULL);
	clock->elapsed = (size_t)((clock->end.tv_sec - clock->start.tv_sec) \
		* 1000 + (clock->end.tv_usec - clock->start.tv_usec) / 1000);
	clock->start = clock->end;
}
