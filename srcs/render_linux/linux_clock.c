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

# include "render_linux.h"

void	start_clock(t_clock *clock)
{
	ftime(&clock->start);
}

void	update_clock(t_clock *clock)
{
	ftime(&clock->end);
	clock->elapsed = (size_t) (1000.0 * (clock->end.time - clock->start.time)
	+ (clock->end.millitm - clock->start.millitm));
	clock->start = clock->end;
}