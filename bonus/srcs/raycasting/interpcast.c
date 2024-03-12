/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doorcast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:52:50 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 21:52:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	setup_interp_cast(t_game *game, t_sprite *sprite, t_interp_cast *cast);

static inline void	draw_interp_line(t_game *game, t_interp_cast *cast)
{
	cast->shade_perc = (float)(cast->draw_st_x - cast->shade_save_x) \
		/ (float)cast->tex_pix_width;
	cast->shade_final = cast->start.shade * (1 - cast->shade_perc) \
		+ cast->end.shade * cast->shade_perc;
	cast->this_line_step_y = 1.0f * cast->tex->width \
		/ cast->this_line_h;
	cast->out_screen_y = (0 - cast->draw_st_y) * (cast->draw_st_y < 0);
	cast->this_line_exact_y = cast->this_line_step_y \
		* cast->out_screen_y;
	cast->draw_st_y = ft_max(cast->draw_st_y, 0);
	cast->draw_end_y = ft_min(cast->draw_end_y, cast->h - 1);
	while (cast->draw_st_y < cast->draw_end_y)
	{
		cast->tex_pix_y = (int)cast->this_line_exact_y;
		cast->this_line_exact_y += cast->this_line_step_y;
		cast->color = tex_get_pixel(&game->win, cast->tex, cast->tex_pix_x \
			* cast->tex->width + cast->tex_pix_y);
		if (cast->color != 0)
		{
			cast->color = add_shade(cast->color, cast->shade_final);
			game->win.set_pixel(&game->win, cast->draw_st_x, \
				cast->draw_st_y, cast->color);
		}
		cast->draw_st_y++;
	}
}

void	draw_interp(t_game *game, t_sprite *sprite, t_interp_cast *cast)
{
	cast->draw_st_x = ft_max(cast->start.screen_x, 0);
	cast->draw_end_x = ft_min(cast->end.screen_x, cast->w - 1);
	while (cast->draw_st_x < cast->draw_end_x)
	{
		cast->tex_pix_x = (int)(cast->tex_exact_x);
		if (cast->inverted)
			cast->tex_pix_x = cast->tex->height - cast->tex_pix_x - 1;
		cast->tex_exact_x += cast->tex_step_x;
		cast->draw_st_y = (int)(cast->pix_exact_min_y);
		cast->draw_end_y = (int)(cast->pix_exact_max_y);
		cast->this_line_h = cast->draw_end_y - cast->draw_st_y;
		if ((cast->door != NULL \
		&& cast->this_line_h >= game->hori_rays[cast->draw_st_x].line_h) \
		|| (cast->bullet != NULL \
		&& (int)(cast->this_line_h / sprite->height) + 50 \
		>= game->hori_rays[cast->draw_st_x].line_h))
			draw_interp_line(game, cast);
		cast->pix_exact_min_y += cast->step_tex_min_y;
		cast->pix_exact_max_y += cast->step_tex_max_y;
		cast->draw_st_x++;
	}
}

void	interpcast(t_game *game, t_sprite *sprite)
{
	t_interp_cast	cast;

	cast = (t_interp_cast){};
	if (!setup_interp_cast(game, sprite, &cast))
		return ;
	draw_interp(game, sprite, &cast);
}
