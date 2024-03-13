/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:55:51 by cjoao-me          #+#    #+#             */
/*   Updated: 2024/03/08 14:55:51 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "float.h"
# include "stdint.h"
# include "libft.h"
# include "pixel_point.h"
# include "drawing_algos.h"
# include "parsing.h"
# include "render_linux.h"
# include "vector.h"
# include "player.h"
# include "generic_utils.h"

//helper struct for collisions
typedef struct s_move_colli
{
	t_map		*map;
	int			fixed_x;
	int			fixed_y;
	float		unit_size;
	float		potential_len;
	int			divide_potential;
	t_vec2d		player;
	t_vec2d		add;
	t_vec2d		nearest;
	t_vec2d		ray_to_nearest;
	float		ray_length;
	float		overlap;
}				t_move_colli;

//helper struct to draw wall lines
typedef struct t_wall_line
{
	int			line_start;
	int			line_end;
	float		x_hit;
	int			tex_pix_x;
	int			tex_pix_y;
	float		step;
	float		tex_exact_y_save;
	float		tex_exact_y;
	int			y_start;
	int			y_end;
	int			color;
	float		shade_wgt;
	int			x;
	t_mlx_img	*tex;
}	t_wall_line;

//ray struct for raycasting
typedef struct s_ray
{
	int			w;
	int			h;
	float		cam_x;
	t_vec2d		dir_vec;
	t_vec2d		plane;
	t_vec2d		player_sqr;
	t_vec2d		start;
	t_vec2d		first;
	t_vec2d		step;
	t_vec2d		axis_move;
	t_vec2d		ray_dir;
	int			side;
	int			pitch_mod;
	float		z_mod;
	int			hgt_mod;
	float		wall_dist;
}	t_ray;

//struct to save horizontal DDA results
typedef struct s_dda_hor
{
	int		min_y;
	int		max_y;
	int		side;
	float	wall_dist;
	int		line_h;
	float	shade_wgt;
	int		reflect_num;
	int		reflect_den;
}	t_dda_hor;

//struct to save floor rendering results
typedef struct s_dda_ver
{
	float	row_distance;
}	t_dda_ver;

//main game structure
typedef struct s_game
{
	t_parsing	parsing;
	t_map		map;
	t_win		win;
	t_player	player;
	t_dda_hor	*hori_rays;
	t_dda_ver	*verti_rays;
	int			maxmin_hori;
	int			minmax_hori;
	t_mlx_img	tex[NUM_TEX];
	int			colors[NUM_TEX];
	float		max_vis_dist;
	float		wall_reflection;
	int			exit_status;
}	t_game;

//settings.c
void	apply_all_settings(t_game *game);

//game_setup.c
int		game_start(t_game *game, char *game_config);
int		free_game(t_game *game);
void	game_setup_keys(t_game *game);

//game_render.c
int		game_render(t_game *game);
void	game_actions(t_game *game);
void	update_sprites(t_game *game);

//win_render_loop.c
int		rendering_loop(t_game *game);

//handle_collisions.c
void	handle_collisions(t_game *game, t_vec2d *posi, \
		t_vec2d potencial, float unit_size);
void	render_map_inside_compass(t_game *game);
void	render_player_inside_compass(t_game *game);

// game_key_manager.c
void	game_key_manager(t_game *game);

//game_manager_mouse.c
void	game_mouse_manager(t_game *game);

void	player_actions(t_game *game);
void	player_rotate_and_pitch(t_game *game);
void	move_player(t_game *game, int keys);

//////////////////////////////////////
//////        RAYCASTING          ////
//////////////////////////////////////
void	hori_raycasting(t_game *game);
void	wallcast(t_game *game, t_ray *ray, t_dda_hor *hori, int x);
void	floorcast_rgb(t_game *game);
void	ceiling_rgb(t_game *game);

//game_rotate.c
void	setup_all_angles(t_game *game, float rad);
void	game_starting_angle(t_game *game, char direction);
void	game_find_player_set_angles(t_game *game);
void	game_rotate_view_angle(t_game *game, float diff);

//game_loud_textures.c
int		game_load_textures(t_game *game);

//tex_get_pixel.c
int		tex_get_pixel(t_win *win, t_mlx_img *tex, int index);

#endif
