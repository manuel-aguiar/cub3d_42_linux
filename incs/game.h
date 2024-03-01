/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:45:11 by marvin            #+#    #+#             */
/*   Updated: 2024/01/11 14:45:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

# include <float.h>

# include "libft.h"
# include "pixel_point.h"
# include "compass.h"
# include "drawing_algos.h"
# include "parsing.h"
# include "render_linux.h"
# include "vector.h"
# include "player.h"
# include "generic_utils.h"
# include "xpm_parser.h"
# include "sprites.h"


typedef struct s_hud
{
	t_pixel bar_bot_left;
	t_pixel bar_top_left;

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
	t_xpm_tex 	*tex;
}	t_wall_line;

typedef struct s_floor_line
{
	t_xpm_tex	*tex;
	int			win_h;
	int			win_w;
	t_vec2d	ray_left;
	t_vec2d	ray_right;
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

typedef struct s_ray
{
	int			w;
	int			h;
	float 		cam_x;
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
	t_xpm_tex 	*tex;
	int			color;
}	t_sp_cast;

typedef struct s_game
{
	t_parsing	parsing;
	t_map		map;
	t_compass	compass;
	t_win		win;
	t_player	player;			//pointers because GLFW requires globals, change to stack with MLX;
	int			*key_defs;
	t_dda_hor	*hori_rays;
	t_dda_ver	*verti_rays;
	int			maxmin_hori;
	int			minmax_hori;
	float		max_vis_dist;
	float		wall_reflection;
	t_xpm_tex	*tex[NUM_TEX];
	t_sprite	*sprites;
	t_sprite	**sorted;
	int			sprite_count;
	float		floating;
	float		float_sense;
	float		float_sin;
	int			max_bullets;
	int			live_bullets;
	t_door		template_door;
	t_medi		template_medi;
	t_ammo		template_ammo;
	t_enemy		template_enemy;
	t_bullet	template_bullet;
	t_clock		clock;
}	t_game;

//settings.c
void    apply_all_settings(t_game *game);

//game_setup.c
int		game_start(t_game *game, char *game_config);
void	free_game(t_game *game);
void	game_setup_keys(t_game *game);

//game_render.c
void	game_render(t_game *game);
void	game_actions(t_game *game);


int		win_render(t_game *game, t_win *win, void (*win_key_press)());

//handle_collisions.c
void	handle_collisions(t_game *game, t_vec2d *posi, t_vec2d potencial, float unit_size);

//
void	render_map_inside_compass(t_game *game);
void	render_player_inside_compass(t_game *game);

// game_key_manager.c
void	game_key_manager(t_game *game);

//game_manager_mouse.c
void	game_mouse_manager(t_game *game);


void	xpm_to_window(t_win *win, t_xpm_tex *tex, t_pixel corner, int pixel_wid, int pixel_hgt);

void	player_actions(t_game *game);
void	player_rotate_and_pitch(t_game *game);

void    move_player(t_game *game, int keys);



//////////////////////////////////////
//////        RAYCASTING          ////
//////////////////////////////////////
int		add_shade(int color, float perc);
void	hori_raycasting(t_game *game);
void	sprite_cast(t_game *game);
void	doorcast(t_game *game, t_sprite *sprite);
void	floorcast(t_game *game);
void	wallcast(t_game *game, t_ray *ray, t_dda_hor *hori, int x);

//////////////////////////////////////
//////        SPRITES             ////
//////////////////////////////////////
int		setup_sprites(t_game *game);
void	sprite_calc_dist(t_game *game);
void    clean_hitmap(t_game *game);
void    setup_hitmap(t_game *game);
void	sprite_place_hitmap(t_game *game, t_sprite *sprite);
float	vertical_coefficient(t_game *game);

//game_render_hud.c
void	render_stats_bars(t_game *game);



t_vec3d bullet_rest(t_game *game, t_bullet *bullet);

//game_rotate.c
void	setup_all_angles(t_game *game, float rad);
void	game_starting_angle(t_game *game, char direction);
void	game_find_player_set_angles(t_game *game);
void	game_rotate_view_angle(t_game *game, float diff);

//update_medi_ammo.c
void		update_medikit(t_game *game, t_sprite *sprite);
void		update_ammokit(t_game *game, t_sprite *sprite);

//update_bullet.c
void		update_bullet(t_game *game, t_sprite *sprite);

//update_enemy_move.c
void		update_enemy(t_game *game, t_sprite *sprite);
void		enemy_movement(t_game *game, t_sprite *sprite, t_enemy *enemy);

//update_door.c
void		update_door(t_game *game, t_sprite *sprite);
int			extract_enemy(t_game *game, t_map *map, int place, int map_index);
int			extract_ammo(t_game *game, t_map *map, int place, int map_index);
int			extract_medi(t_game *game, t_map *map, int place, int map_index);
int			extract_door(t_game *game, t_map *map, int place, int map_index);

#endif