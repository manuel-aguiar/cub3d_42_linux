/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:18:10 by cjoao-me          #+#    #+#             */
/*   Updated: 2024/03/08 14:18:10 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "libft.h"
# include "vector.h"
# include "parsing.h"
# include "render_linux.h"
# include "hit_detection.h"
# include "float.h"

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

typedef struct s_dda_ver
{
	float	row_distance;
}	t_dda_ver;

typedef enum e_sprite_type
{
	MEDIKIT,
	AMMOKIT,
	ENEMY,
	DOOR,
	BULLET,
}	t_sprite_type;

typedef enum e_sprite_status
{
	GONE,
	ON_WALL,
	ON_FLOOR,
	ON_CEIL,
	VISIBLE,
	NOT_VIS,
}	t_sprite_status;

typedef enum e_door_dir
{
	NS,
	WE,
}	t_door_dir;

typedef enum e_rendir
{
	STRAIGHT,
	INVERTED,
}	t_rendir;

typedef enum e_door_state
{
	DOOR_OPEN,
	DOOR_CLOSED,
}	t_door_state;

//main door struct
typedef struct s_door
{
	t_vec2d				base_position;
	int					map_index;
	t_door_state		state;
	t_door_dir			orient;
	t_dda_hor			start;
	t_dda_hor			end;
	float				base_z;
	float				height;
	bool				visible;
	float				wall_start;
	float				wall_end;
	int					start_x;
	int					end_x;
	float				move_sense;
	float				dist_sense;
}	t_door;

//main ammokit struct
typedef struct s_ammo
{
	int					ammopoints;
	float				base_z;
	float				z_sense;
	float				unit_size;
	float				height;
	float				width;
	float				float_radius;
}	t_ammo;

//main medikit structure
typedef struct s_medi
{
	int					lifepoints;
	float				float_radius;
	float				base_z;
	float				z_sense;
	float				unit_size;
	float				height;
	float				width;
}	t_medi;

typedef enum e_enemy_type
{
	X_ENEMY,
	Y_ENEMY,
	Z_ENEMY,
}	t_enemy_type;

//main enemy structure
typedef struct s_enemy
{
	t_enemy_type		type;
	int					ms_to_swap;
	int					elapsed;
	float				base_z;
	float				z_sense;
	float				move_sense;
	float				unit_size;
	float				height;
	float				width;
	int					attack_val;
	int					health;
	int					attack_time;
	int					attack_elapsed;
	int					cur_shot_time;
	int					shot_this_time;
	int					shot_max_time;
}	t_enemy;

typedef enum e_bullet_shooter
{
	B_ME,
	B_ENEMY,
}	t_bullet_shooter;

//main bullet structure
typedef struct s_bullet
{
	t_bullet_shooter	shooter;
	t_vec3d				dir;
	float				dir_len;
	t_vec3d				posi;
	float				base_z;
	float				move_sense;
	float				unit_size;
	float				height;
	int					attack_val;
	t_vec3d				hole;
	bool				wall_hole;
}	t_bullet;

//main sprite structure
typedef struct s_sprite
{
	t_sprite_type		type;
	t_sprite_status		status;
	t_vec2d				posi;
	float				cur_z;
	float				dist;
	float				height;
	float				width;
	float				unit_size;
	t_clock				clock;
	t_textures			tex;
	void				*data;
	bool				inverted;
	t_hitnode			my_hit[4];
}	t_sprite;

int		sprite_qs_comp(t_sprite *first, t_sprite *second);
void	sprite_qs_distance(t_sprite **sprites, int sprite_count, \
		int (*cmp)(t_sprite *, t_sprite *));

#endif
