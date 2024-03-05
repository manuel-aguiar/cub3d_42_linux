/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_help_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:14:30 by codespace         #+#    #+#             */
/*   Updated: 2024/03/05 12:38:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_linux.h"

void	pause_text_string(t_win *win)
{
	mlx_string_put(win->mlx, win->mlx_win, win->width / 2, win->height / 2, 0xffffff, \
	"brah cenas ya ja meto alguma coisa");
}

void	you_lost_text_string(t_win *win)
{
	mlx_string_put(win->mlx, win->mlx_win, win->width / 2, win->height / 2, 0xffffff, \
	"You lost!!");
}

void	enemies_defeated_text_string(t_win *win)
{
	mlx_string_put(win->mlx, win->mlx_win, win->width / 2, win->height * 3 / 4, 0xffffff, \
	"You beat all enemies!! Press P if you want to keep exploring");
}
