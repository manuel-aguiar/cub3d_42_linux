/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_callback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:16:54 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 12:16:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_linux.h"

int	key_release(int keycode, t_win *win)
{
	if (keycode == KEY_ESC)
		win->keys &= ~(1 << BIT_ESC);
	else if (keycode == KEY_FRONT)
		win->keys &= ~(1 << BIT_FRONT);
	else if (keycode == KEY_BACK)
		win->keys &= ~(1 << BIT_BACK);
	else if (keycode == KEY_LEFT)
		win->keys &= ~(1 << BIT_LEFT);
	else if (keycode == KEY_RIGHT)
		win->keys &= ~(1 << BIT_RIGHT);
	else if (keycode == KEY_ROT_L)
		win->keys &= ~(1 << BIT_ROT_L);
	else if (keycode == KEY_ROT_R)
		win->keys &= ~(1 << BIT_ROT_R);
	return (1);
}

int	key_press(int keycode, t_win *win)
{
	if (keycode == KEY_ESC)
		win->keys |= (1 << BIT_ESC);
	else if (keycode == KEY_FRONT)
		win->keys |= (1 << BIT_FRONT);
	else if (keycode == KEY_BACK)
		win->keys |= (1 << BIT_BACK);
	else if (keycode == KEY_LEFT)
		win->keys |= (1 << BIT_LEFT);
	else if (keycode == KEY_RIGHT)
		win->keys |= (1 << BIT_RIGHT);
	else if (keycode == KEY_ROT_L)
		win->keys |= (1 << BIT_ROT_L);
	else if (keycode == KEY_ROT_R)
		win->keys |= (1 << BIT_ROT_R);
	return (1);
}
