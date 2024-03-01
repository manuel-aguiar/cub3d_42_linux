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

# include "render_linux.h"

void	key_release(int keycode)
{
	if (keycode == KEY_ESC)
		g_keys &= ~(1 << BIT_ESC);
	else if (keycode == KEY_FRONT)
		g_keys &= ~(1 << BIT_FRONT);
	else if (keycode == KEY_BACK)
		g_keys &= ~(1 << BIT_BACK);
	else if (keycode == KEY_LEFT)
		g_keys &= ~(1 << BIT_LEFT);
	else if (keycode == KEY_RIGHT)
		g_keys &= ~(1 << BIT_RIGHT);
	else if (keycode == KEY_JUMP)
		g_keys &= ~(1 << BIT_JUMP);
	else if (keycode == KEY_SPRINT)
		g_keys &= ~(1 << BIT_SPRINT);
	else if (keycode == KEY_CROUCH)
		g_keys &= ~(1 << BIT_CROUCH);
	else if (keycode == KEY_PRONE)
		g_keys &= ~(1 << BIT_PRONE);
}

/*
	BIT_BLUR_T,
	BIT_FLOOR_REFL_T,
	BIT_SHADE_T,
	BIT_PAUSE_T,

*/

void	key_press_toggle(int keycode)
{
	if (keycode == KEY_BLUR_T)
	{
		if (!((g_keys >> BIT_BLUR_T) & 1))
			g_keys |= (1 << BIT_BLUR_T);
		else
			g_keys &= ~(1 << BIT_BLUR_T);			
	}
	else if (keycode == KEY_FLOOR_REFL_T)
	{
		if (!((g_keys >> BIT_FLOOR_REFL_T) & 1))
			g_keys |= (1 << BIT_FLOOR_REFL_T);
		else
			g_keys &= ~(1 << BIT_FLOOR_REFL_T);			
	}
	else if (keycode == KEY_CEIL_REFL_T)
	{
		if (!((g_keys >> BIT_CEIL_REFL_T) & 1))
			g_keys |= (1 << BIT_CEIL_REFL_T);
		else
			g_keys &= ~(1 << BIT_CEIL_REFL_T);			
	}
	else if (keycode == KEY_SHADE_T)
	{
		if (!((g_keys >> BIT_SHADE_T) & 1))
			g_keys |= (1 << BIT_SHADE_T);
		else
			g_keys &= ~(1 << BIT_SHADE_T);			
	}
	else if (keycode == KEY_PAUSE_T)
	{
		if (!((g_keys >> BIT_PAUSE_T) & 1))
			g_keys |= (1 << BIT_PAUSE_T);
		else
			g_keys &= ~(1 << BIT_PAUSE_T);			
	}
	else if (keycode == KEY_HUD_T)
	{
		if (!((g_keys >> BIT_HUD_T) & 1))
			g_keys |= (1 << BIT_HUD_T);
		else
			g_keys &= ~(1 << BIT_HUD_T);			
	}
}

void	key_press(int keycode)
{
	if (keycode == KEY_ESC)
		g_keys |= (1 << BIT_ESC);
	else if (keycode == KEY_FRONT)
		g_keys |= (1 << BIT_FRONT);
	else if (keycode == KEY_BACK)
		g_keys |= (1 << BIT_BACK);
	else if (keycode == KEY_LEFT)
		g_keys |= (1 << BIT_LEFT);
	else if (keycode == KEY_RIGHT)
		g_keys |= (1 << BIT_RIGHT);
	else if (keycode == KEY_JUMP)
		g_keys |= (1 << BIT_JUMP);
	else if (keycode == KEY_SPRINT)
		g_keys |= (1 << BIT_SPRINT);
	else if (keycode == KEY_CROUCH)
		g_keys |= (1 << BIT_CROUCH);
	else if (keycode == KEY_PRONE)
		g_keys |= (1 << BIT_PRONE);
	key_press_toggle(keycode);
}



void	win_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS)
		key_press(key);
	else if (action == GLFW_RELEASE)
		key_release(key);
	
}