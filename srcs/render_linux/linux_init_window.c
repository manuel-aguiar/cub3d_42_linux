/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:13:01 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 10:13:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "render_linux.h"

int	win_init_window(t_win *win)
{
	if (!glfwInit())
        return (0);      // no free, potencial memleak
	win->window = glfwCreateWindow(win->width, win->height, win->name, NULL, NULL);
	if (!win->window)
	{
		glfwTerminate();
		return (0);		// no free, potencial memleak
	}
	glfwMakeContextCurrent(win->window);
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return (0);		// no free, potencial memleak
	}
	win->front_buf = malloc(sizeof(*win->front_buf) * win->width * win->height * win->rgb_size);
	win->blur.first = malloc(sizeof(*win->blur.first) * win->width * win->height * win->rgb_size);
	win->blur.second = malloc(sizeof(*win->blur.second) * win->width * win->height * win->rgb_size);
	win->blur.save_front = malloc(sizeof(*win->blur.save_front) * win->width * win->height * win->rgb_size);
	win->blur.clock = (t_clock){};
	ftime(&win->blur.clock.start);
	if (!win->front_buf || !win->blur.first || !win->blur.second || !win->blur.save_front)
		return (perror_msg_int("malloc", 0));		// no free, potencial memleak
	win->set_pixel = win_set_pixel;
	win->get_pixel = win_get_pixel;
	glfwSetInputMode(win->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetInputMode(win->window, GLFW_STICKY_KEYS, GLFW_FALSE);
	glfwSetInputMode(win->window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_FALSE);
	return (1);	
}

int	free_win_glfw(t_win *win)
{
	glfwSetInputMode(win->window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetInputMode(win->window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	glfwSetInputMode(win->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwDestroyWindow(win->window);
	glfwTerminate();
	if (win->front_buf)
		free(win->front_buf);
	if (win->blur.first)
		free(win->blur.first);
	if (win->blur.second)
		free(win->blur.second);
	if (win->blur.save_front)
		free(win->blur.save_front);
	return (1);
}