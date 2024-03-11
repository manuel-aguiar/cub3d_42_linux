/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceilcast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:09:47 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 16:01:21 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	setup_common_ceiling_line(t_game *game, t_floor_line *line)
{
	t_vec2d	dir;

	dir = vec2d_multi(vec2d_multi(game->player.dir_vec, \
		game->player.cur_dir_len), 1);
	line->win_h = game->win.height;
	line->win_w = game->win.width;
	line->ray_left = vec2d_add(dir, game->player.plane);
	line->ray_right = vec2d_sub(dir, game->player.plane);
	line->row_z = (1 - (game->player.cur_z + game->player.jump_z_mod \
		+ game->player.walk_z_mod)) * line->win_h;
	line->pitch_mod = line->win_h / 2 + game->player.pitch;
	line->tex = &game->tex[C_TEX];
}

static inline void	setup_this_ceiling_line(t_game *game, t_floor_line *line, \
					int y)
{
	int	this_pitch;

	this_pitch = y - line->pitch_mod;
	line->row_dist = float_ternary(float_equal(line->pitch_mod, 0, 0.0001f), \
		2000, line->row_z / this_pitch);
	line->tile_step_x = line->row_dist * (line->ray_right.x - \
		line->ray_left.x) / line->win_w;
	line->tile_step_y = line->row_dist * (line->ray_right.y - \
		line->ray_left.y) / line->win_w;
	line->tile_exact_x = game->player.map_posi.x + line->row_dist \
		* line->ray_right.x;
	line->tile_exact_y = game->player.map_posi.y + line->row_dist \
		* line->ray_right.y;
	line->shade_wgt = float_clamp(ft_fabs(line->row_dist / game->max_vis_dist \
		* game->player.cur_dir_len / game->player.base_dir_len), 0.0f, 1.0f);
}

static inline void	ceiling_hori_line(t_game *game, t_floor_line *line, \
										int *x, int y)
{
	line->tile_x = (int)(line->tile_exact_x);
	line->tile_y = (int)(line->tile_exact_y);
	line->tex_pix_x = ft_abs((int)(line->tex->width \
		* (line->tile_exact_x - line->tile_x)) % line->tex->width);
	line->tex_pix_y = ft_abs((int)(line->tex->height \
		* (line->tile_exact_y - line->tile_y)) % line->tex->height);
	line->tile_exact_x -= line->tile_step_x;
	line->tile_exact_y -= line->tile_step_y;
	line->color = tex_get_pixel(&game->win, line->tex, line->tex->width \
		* line->tex_pix_y + line->tex_pix_x);
	line->color = add_shade(line->color, line->shade_wgt);
	if (((game->win.keys) >> BIT_CEIL_REFL_T) & 1 \
	&& y < game->hori_rays[*x].max_y + game->hori_rays[*x].line_h)
		line->color = avg_colour(game->win.get_pixel(&game->win, *x, y), \
		line->color, game->hori_rays[*x].reflect_num, \
		game->hori_rays[*x].reflect_den);
	game->win.set_pixel(&game->win, *x, y, line->color);
	(*x)++;
	while (*x < line->win_w && y <= game->hori_rays[*x].max_y)
	{
		line->tile_exact_x -= line->tile_step_x;
		line->tile_exact_y -= line->tile_step_y;
		(*x)++;
	}
}

void	ceiling_rgb(t_game *game)
{
	t_verti_line	line;

	line.color = game->map.tex_data[C_TEX].color;
	line.x = 0;
	line.max_y = game->win.height - 1;
	while (line.x < game->win.width)
	{
		line.min_y = int_clamp(game->hori_rays[line.x].max_y + 1, \
			0, game->win.height - 1);
		if (line.min_y != line.max_y)
			draw_vertical_line(&game->win, &line);
		line.x++;
	}
}

void	ceilcast(t_game *game)
{
	t_floor_line	line;
	int				x;
	int				y;

	if (game->map.tex_data[C_TEX].type == COLOR_TEX)
		return (ceiling_rgb(game));
	setup_common_ceiling_line(game, &line);
	y = ft_max(game->minmax_hori + 1, 0);
	while (y < line.win_h)
	{
		setup_this_ceiling_line(game, &line, y);
		x = 0;
		while (x < line.win_w)
			ceiling_hori_line(game, &line, &x, y);
		y++;
	}
}
