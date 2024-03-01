/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_render_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:21:38 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 10:21:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

int		win_render(t_game *game, t_win *win, void (*win_key_press)())
{	
	(void)win_key_press;
	glfwSetKeyCallback(win->window, win_key_callback);
	glfwSetMouseButtonCallback(win->window, win_mouse_button_callback);
	glfwSetScrollCallback(win->window, win_mouse_scroll_callback);
	glViewport(0, 0, win->width, win->height);
	glfwSetCursorPos(win->window, win->width / 2, win->height / 2);
	start_clock(&game->clock);
    while (!glfwWindowShouldClose(win->window))
	{
		glRasterPos2f(-1, -1);

		glfwGetCursorPos(win->window, &game->mouse->cur_x, &game->mouse->cur_y);
		
		game_actions(game);
		glfwSetCursorPos(win->window, win->width / 2, win->height / 2);	

		game_render(game);
		glClear(GL_COLOR_BUFFER_BIT);
        glDrawPixels(win->width, win->height, GL_RGBA, GL_UNSIGNED_BYTE, win->front_buf);
		glfwSwapBuffers(win->window);
        glfwPollEvents();
    }
	return (1);
}
