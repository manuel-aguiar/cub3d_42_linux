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

void win_mouse_scroll_callback(GLFWwindow* window, \
	double xoffset, double yoffset) 
{
    (void)window;
	(void)xoffset;
	(void)yoffset;
}

void    mouse_release(int keycode)
{
	if (keycode == BUT_SHOOT)
		g_mouse.buttons &= ~(1 << BIT_SHOOT);
}

void    mouse_press(int keycode)
{
	if (keycode == BUT_AIM)
	{
		if (!((g_mouse.buttons >> BIT_AIM) & 1))
			g_mouse.buttons |= (1 << BIT_AIM);
		else
			g_mouse.buttons &= ~(1 << BIT_AIM);	
	}
	else if (keycode == BUT_SHOOT)
		g_mouse.buttons |= (1 << BIT_SHOOT); 
}

void win_mouse_button_callback(GLFWwindow* window, int button, \
	int action, int mods)
{
    (void)mods;
	(void)window;

	if (action == GLFW_PRESS)
		mouse_press(button);
	else if (action == GLFW_RELEASE)
        mouse_release(button);
}