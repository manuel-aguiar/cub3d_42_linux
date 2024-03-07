/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriteibles.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:55:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 09:55:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SPRITES_H

# define SPRITES_H

# include "libft.h"
# include "vector.h"
# include "parsing.h"
# include "render_linux.h"
# include "hit_detection.h"
# include <float.h>

typedef struct s_dda_hor
{
	int 	min_y;
	int 	max_y;
	int		side;
	float 	wall_dist;
	int		line_h;
	float	shade_wgt;
	int		reflect_num;
	int		reflect_den;
}	t_dda_hor;

typedef struct s_dda_ver
{
	float row_distance;
}	t_dda_ver;

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
	float 		times;
	float 		dir_z;
	float 		coefficient;
}	t_verti_coef;

typedef enum
{
	MEDIKIT,
	AMMOKIT,
	ENEMY,
	DOOR,
	BULLET,
}	e_sprite_type;

typedef enum
{
	GONE,
	ON_WALL,
	ON_FLOOR,
	ON_CEIL,
	VISIBLE,
	NOT_VIS,
}	e_sprite_status;

typedef enum
{
	NS,
	WE,
}	e_door_dir;

typedef enum
{
	STRAIGHT,
	INVERTED,
}	e_rendir;

typedef enum
{
	DOOR_OPEN,
	DOOR_CLOSED,
}	e_door_state;

typedef struct s_door
{
	t_vec2d				base_position;
	int					map_index;
	e_door_state		state;
	e_door_dir			orient;
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

typedef struct s_ammo
{
	int 				ammopoints;
	float				base_z;
	float				z_sense;
	float				unit_size;
	float				height;
	float				width;
	float				float_radius;
}	t_ammo;

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

typedef enum
{
	X_ENEMY,
	Y_ENEMY,
	Z_ENEMY,
}	e_enemy_type;

typedef struct s_enemy
{
	e_enemy_type		type;
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
}	t_enemy;

typedef enum
{
	B_ME,
	B_ENEMY,
}	e_bullet_shooter;

typedef struct s_bullet
{
	e_bullet_shooter	shooter;
	t_vec3d				dir;
	float				dir_len;
	t_vec3d				posi;
	float				base_z;
	float				move_sense;
	float				unit_size;
	float				height;
	int					attack_val;
	t_vec3d				hole;
}	t_bullet;

typedef struct s_exit
{
	float				base_z;
	float				z_sense;
	float				unit_size;
	float				height;
	float				width;
}	t_exit;

typedef struct s_sprite
{
	e_sprite_type		type;
	e_sprite_status		status;
	t_vec2d				posi;
	float				cur_z;
	float				dist;
	float				height;
	float				width;
	float				unit_size;
	t_clock				clock;
	e_textures			tex;
	void				*data;
	bool				inverted;
	t_hitnode			my_hit[4];
}	t_sprite;

int	sprite_qs_comp(t_sprite *first, t_sprite *second);
void	sprite_qs_distance(t_sprite **sprites, int sprite_count, int (*cmp)(t_sprite * , t_sprite *));


#endif

