/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallcast_reflection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:53:41 by marvin            #+#    #+#             */
/*   Updated: 2024/02/16 16:53:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	setup_wall_line(t_game *game, t_ray *ray, \
					t_dda_hor *hori, t_wall_line *line)
{
	line->line_start = hori->min_y;
	line->line_end = hori->max_y;
	line->x_hit = float_ternary(hori->side == 0, \
		game->player.map_posi.y + hori->wall_dist * ray->ray_dir.y, \
		game->player.map_posi.x + hori->wall_dist * ray->ray_dir.x);
	line->tex = ptr_ternary(hori->side == 0, \
		ptr_ternary(game->player.map_posi.x + hori->wall_dist \
		* ray->ray_dir.x < game->player.map_posi.x, \
		&game->tex[WE_TEX], &game->tex[EA_TEX]), \
		ptr_ternary(game->player.map_posi.y + hori->wall_dist \
		* ray->ray_dir.y < game->player.map_posi.y, \
		&game->tex[SO_TEX], &game->tex[NO_TEX]));
	line->x_hit -= (int)(line->x_hit);
	line->tex_pix_x = (int)(line->x_hit * (float)(line->tex->height));
	if (hori->side == 0 && ray->ray_dir.x > 0)
		line->tex_pix_x = (line->tex->height) - line->tex_pix_x - 1;
	if (hori->side == 1 && ray->ray_dir.y < 0)
		line->tex_pix_x = (line->tex->height) - line->tex_pix_x - 1;
	line->step = 1.0f * line->tex->width / hori->line_h;
	line->tex_exact_y_save = (line->line_start - ray->hgt_mod \
		+ hori->line_h / 2) * line->step;
	line->shade_wgt = hori->wall_dist / game->max_vis_dist \
		* game->player.cur_dir_len / game->player.base_dir_len;
}

static void	standard_wall(t_game *game, t_ray *ray, \
						t_wall_line *line)
{
	line->tex_exact_y = line->tex_exact_y_save;
	line->tex_exact_y += line->step * (0 - line->line_start) \
		* (line->line_start < 0);
	line->y_start = ft_max(line->line_start, 0);
	line->y_end = ft_min(line->line_end, ray->h - 1);
	while (line->y_start < line->y_end)
	{
		line->tex_pix_y = (int)line->tex_exact_y;
		line->tex_exact_y += line->step;
		line->color = tex_get_pixel(&game->win, line->tex, line->tex_pix_x \
			* line->tex->width + line->tex_pix_y);
		game->win.set_pixel(&game->win, line->x, line->y_start, line->color);
		line->y_start++;
	}
}

void	wallcast(t_game *game, t_ray *ray, t_dda_hor *hori, int x)
{
	t_wall_line	line;

	setup_wall_line(game, ray, hori, &line);
	line.x = x;
	standard_wall(game, ray, &line);
}
