/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_text_strings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:14:30 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 23:13:07 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_linux.h"

void	loading_text_string(t_win *win)
{
	mlx_string_put(win->mlx, win->mlx_win, win->width / 2, win->height / 2, \
		0xffffff, \
		"Loading...");
}

void	pause_text_string(t_win *win)
{
	mlx_string_put(win->mlx, win->mlx_win, win->width / 2, win->height / 2, \
		0xffffff, \
		"brah cenas ya ja meto alguma coisa");
}

void	you_lost_text_string(t_win *win)
{
	mlx_string_put(win->mlx, win->mlx_win, win->width / 2, win->height / 2, \
		0xffffff, \
		"You lost!!");
}

void	enemies_defeated_text_string(t_win *win)
{
	mlx_string_put(win->mlx, win->mlx_win, win->width * 2 / 3, \
		win->height * 3 / 4, 0xffffff, \
		"You defeated all enemies!!");
}
