/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_callback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:17:03 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 12:17:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "render_linux.h"

int    mouse_press(int button, int x, int y, t_win *win)
{
	(void)x;
	(void)y;
	if (button == BUT_AIM)
	{
		if (!((win->mouse.buttons >> BIT_AIM) & 1))
			win->mouse.buttons |= (1 << BIT_AIM);
		else
			win->mouse.buttons &= ~(1 << BIT_AIM);	
	}
	else if (button == BUT_SHOOT)
		win->mouse.buttons |= (1 << BIT_SHOOT);
	return (1);
}

int	mouse_release(int button, int x, int y, t_win *win)
{
	(void)x;
	(void)y;
	if (button == BUT_SHOOT)
		win->mouse.buttons &= ~(1 << BIT_SHOOT);
	return (1);
}

int	mouse_position(int x, int y, t_win *win)
{	
	printf("BEFORE mouse: prev %d %d, cur %d %d   ", win->mouse.prev_x, win->mouse.prev_y,win->mouse.cur_x, win->mouse.cur_y);
	win->mouse.prev_x = win->mouse.cur_x;
	win->mouse.prev_y = win->mouse.cur_y;
	win->mouse.cur_x = x;
	win->mouse.cur_y = y;
	printf("AFTER mouse: prev %d %d, cur %d %d\n", win->mouse.prev_x, win->mouse.prev_y,win->mouse.cur_x, win->mouse.cur_y);
	return (1);
}