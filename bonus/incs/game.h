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
# include "compass.h"
# include "drawing_algos.h"
# include "parsing.h"
# include "render_linux.h"
# include "vector.h"
# include "player.h"
# include "generic_utils.h"
# include "sprites.h"

//helper struct for bullet colllisions
typedef struct s_move_colli
{
	t_map		*map;
	t_sprite	*sprite;
	t_door		*door;
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

typedef struct s_hud
{
	t_pixel	bar_bot_left;
	t_pixel	bar_top_left;

}	t_hud;

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

typedef struct s_floor_line
{
	t_mlx_img	*tex;
	int			win_h;
	int			win_w;
	t_vec2d		ray_left;
	t_vec2d		ray_right;
	float		row_z;
	float		pitch_mod;
	float		row_dist;
	float		tile_exact_x;
	float		tile_exact_y;
	float		tile_step_x;
	float		tile_step_y;
	int			tile_x;
	int			tile_y;
	int			tex_pix_x;
	int			tex_pix_y;
	int			color;
	float		shade_wgt;
}	t_floor_line;

//main raycasting struct
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

typedef struct s_sp_cast
{
	int			win_w;
	int			win_h;
	t_vec2d		play_posi;
	t_vec2d		play_dir;
	t_vec2d		play_plane;
	float		inv_camera;
	float		pitch_mod;
	float		play_z_mod;
	t_sprite	*sprite;
	t_vec2d		relative;
	t_vec2d		trans;
	float		sp_z_mod;
	int			total_z_mod;
	int			centre_pix_x;
	int			sp_pix_h;
	int			sp_pix_w;
	int			bot_pix_y;
	int			top_pix_y;
	int			left_pix_x;
	int			right_pix_x;
	float		tex_exact_x;
	float		tex_exact_y;
	float		tex_step_x;
	float		tex_step_y;
	float		shade_wgt;
	int			tex_pix_x;
	int			tex_pix_y;
	t_mlx_img	*tex;
	int			color;
}	t_sp_cast;

typedef struct s_cast_point
{
	t_vec2d	point;
	t_vec2d	relative;
	t_vec2d	trans;
	float	z_mod;
	int		total_z_mod;
	int		screen_x;
	int		height;
	int		min_screen_y;
	int		max_screen_y;
	float	shade;
}	t_cast_point;

typedef struct s_interp_cast
{
	int				w;
	int				h;
	t_vec2d			dir;
	t_door			*door;
	t_bullet		*bullet;
	bool			inverted;
	t_cast_point	start;
	t_cast_point	end;
	float			inv_cam;
	float			pitch_mod;
	float			play_z_mod;
	float			tex_pix_width;
	float			step_tex_min_y;
	float			step_tex_max_y;
	float			tex_step_x;
	float			tex_exact_x;
	int				out_screen_x;
	int				out_screen_y;
	float			pix_exact_min_y;
	float			pix_exact_max_y;
	int				this_line_h;
	float			this_line_step_y;
	float			this_line_exact_y;
	int				tex_pix_x;
	int				tex_pix_y;
	int				shade_save_x;
	float			shade_perc;
	float			shade_final;
	int				color;
	int				draw_st_x;
	int				draw_end_x;
	int				draw_st_y;
	int				draw_end_y;
	t_mlx_img		*tex;
}	t_interp_cast;

typedef struct s_verti_coef
{
	t_ray		ray;
	t_dda_hor	hori;
	t_vec2d		wall_hit;
	int			new_pitch;
	float		new_tan;
	t_vec3d		play_3d;
	t_vec3d		wall_3d;
	t_vec3d		diff;
	float		times;
	float		dir_z;
	float		coefficient;
}	t_verti_coef;

typedef struct s_bullet_colli
{
	t_bullet	*bullet;
	int			map_index;
	t_vec2d		check[2];
	t_vec2d		box[2];
	t_vec2d		collision[2];
}	t_bullet_colli;

typedef struct s_hud_stats
{
	int		health_color;
	int		ammo_color;
	int		empty_color;
	t_pixel	health_start;
	t_pixel	health_end;
	t_pixel	ammo_start;
	t_pixel	ammo_end;
}	t_hud_stats;

/*
	main game structure
	holds all components (player, compass, parsing, templates)
	on the stack, as much as possible
*/
typedef struct s_game
{
	t_parsing	parsing;
	t_map		map;
	t_compass	compass;
	t_win		win;
	t_player	player;
	t_dda_hor	*hori_rays;
	t_dda_ver	*verti_rays;
	int			maxmin_hori;
	int			minmax_hori;
	float		max_vis_dist;
	float		wall_reflection;
	t_mlx_img	tex[NUM_TEX];
	int			colors[NUM_TEX];
	t_sprite	*sprites;
	t_sprite	**sorted;
	int			sprite_count;
	int			enemy_count;
	float		floating;
	float		float_sense;
	float		float_sin;
	int			max_bullets;
	int			live_bullets;
	t_door		template_door;
	t_medi		template_medi;
	t_ammo		template_ammo;
	t_enemy		template_x_enemy;
	t_enemy		template_y_enemy;
	t_enemy		template_z_enemy;
	t_bullet	template_bullet;
	int			cur_time_win_str;
	int			total_time_win_str;
	bool		is_lost;
	int			cur_time_lost_str;
	int			total_time_lost_str;
	t_clock		clock;
	t_hud_stats	stats;
	int			blur_is_on;
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

void	player_walk_height(t_player *player, t_game *game);

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
int		add_shade(int color, float perc);
void	hori_raycasting(t_game *game);
void	sprite_cast(t_game *game);
void	interpcast(t_game *game, t_sprite *sprite);
void	floorcast(t_game *game);
void	ceilcast(t_game *game);
void	wallcast(t_game *game, t_ray *ray, t_dda_hor *hori, int x);

//////////////////////////////////////
//////        SPRITES             ////
//////////////////////////////////////
int		setup_sprites(t_game *game);
void	sprite_calc_dist(t_game *game);
void	clean_hitmap(t_game *game);
void	setup_hitmap(t_game *game);
void	sprite_place_hitmap(t_game *game, t_sprite *sprite);
float	vertical_coefficient(t_game *game);

//game_render_hud.c
void	render_stats_bars(t_game *game);
t_vec3d	bullet_rest(t_game *game, t_bullet *bullet);

//game_rotate.c
void	setup_all_angles(t_game *game, float rad);
void	game_starting_angle(t_game *game, char direction);
void	game_find_player_set_angles(t_game *game);
void	game_rotate_view_angle(t_game *game, float diff);

//update_medi_ammo.c
void	update_medikit(t_game *game, t_sprite *sprite);
void	update_ammokit(t_game *game, t_sprite *sprite);

//update_bullet.c
void	update_bullet(t_game *game, t_sprite *sprite);

//update_enemy_move.c
void	update_enemy(t_game *game, t_sprite *sprite);
void	enemy_movement(t_game *game, t_sprite *sprite, t_enemy *enemy);

//sprites/extract
void	update_door(t_game *game, t_sprite *sprite);
int		extract_x_enemy(t_game *game, t_map *map, int place, int map_index);
int		extract_y_enemy(t_game *game, t_map *map, int place, int map_index);
int		extract_z_enemy(t_game *game, t_map *map, int place, int map_index);
int		extract_ammo(t_game *game, t_map *map, int place, int map_index);
int		extract_medi(t_game *game, t_map *map, int place, int map_index);
int		extract_door(t_game *game, t_map *map, int place, int map_index);

//game_loud_textures.c
int		game_load_textures(t_game *game);

//tex_get_pixel.c
int		tex_get_pixel(t_win *win, t_mlx_img *tex, int index);

//game_rand_gen.c
float	rand_float(float min, float max);
int		rand_int(int min, int max);
void	rand_init(void);

//bullet_start.c
void	start_friendly_bullet(t_game *game);
void	start_enemy_bullet(t_game *game, t_sprite *enemy);

void	player_takes_damage(t_game *game, int damage);

#endif
