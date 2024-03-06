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
	else if (keycode == KEY_JUMP)
		win->keys &= ~(1 << BIT_JUMP);
	else if (keycode == KEY_SPRINT)
		win->keys &= ~(1 << BIT_SPRINT);
	else if (keycode == KEY_CROUCH)
		win->keys &= ~(1 << BIT_CROUCH);
	else if (keycode == KEY_PRONE)
		win->keys &= ~(1 << BIT_PRONE);
	return (1);
}

static inline int	key_press_toggle_cont(int keycode, t_win *win)
{
	if (keycode == KEY_SHADE_T)
	{
		if (!((win->keys >> BIT_SHADE_T) & 1))
			win->keys |= (1 << BIT_SHADE_T);
		else
			win->keys &= ~(1 << BIT_SHADE_T);
	}
	else if (keycode == KEY_PAUSE_T)
	{
		if (!((win->keys >> BIT_PAUSE_T) & 1))
			win->keys |= (1 << BIT_PAUSE_T);
		else
			win->keys &= ~(1 << BIT_PAUSE_T);
	}
	else if (keycode == KEY_HUD_T)
	{
		if (!((win->keys >> BIT_HUD_T) & 1))
			win->keys |= (1 << BIT_HUD_T);
		else
			win->keys &= ~(1 << BIT_HUD_T);
	}
	return (1);
}

static inline int	key_press_toggle(int keycode, t_win *win)
{
	if (keycode == KEY_BLUR_T)
	{
		if (!((win->keys >> BIT_BLUR_T) & 1))
			win->keys |= (1 << BIT_BLUR_T);
		else
			win->keys &= ~(1 << BIT_BLUR_T);
	}
	else if (keycode == KEY_FLOOR_REFL_T)
	{
		if (!((win->keys >> BIT_FLOOR_REFL_T) & 1))
			win->keys |= (1 << BIT_FLOOR_REFL_T);
		else
			win->keys &= ~(1 << BIT_FLOOR_REFL_T);
	}
	else if (keycode == KEY_CEIL_REFL_T)
	{
		if (!((win->keys >> BIT_CEIL_REFL_T) & 1))
			win->keys |= (1 << BIT_CEIL_REFL_T);
		else
			win->keys &= ~(1 << BIT_CEIL_REFL_T);
	}
	else
		return (key_press_toggle_cont(keycode, win));
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
	else if (keycode == KEY_JUMP)
		win->keys |= (1 << BIT_JUMP);
	else if (keycode == KEY_SPRINT)
		win->keys |= (1 << BIT_SPRINT);
	else if (keycode == KEY_CROUCH)
		win->keys |= (1 << BIT_CROUCH);
	else if (keycode == KEY_PRONE)
		win->keys |= (1 << BIT_PRONE);
	else
		return (key_press_toggle(keycode, win));
	return (1);
}
