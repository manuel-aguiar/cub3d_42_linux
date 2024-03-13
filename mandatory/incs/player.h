/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:24:28 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 19:24:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "vector.h"
# include "render_linux.h"
# include "drawing_algos.h"
# include "pixel_point.h"

# define P_MY_PI 3.14159265f

/*
 diagonal of a 90º triangle with sides 1 by 1
 by pitagoras 1^2 + 1^2 = diag^2 so diag = sqrt(2)
 div by 2 heps in getting sine and cosine at +45/-45/+135/-135 angles all
based on one single sin/cos calculation
used on defining character movement
*/
# define P_SQRT_OF_TWO_OVER_TWO 0.7071067f

typedef struct s_player	t_player;

enum e_controls
{
	CTR_CUR,
	CTR_MAX,
	CTR_MIN,
	CTR_SIZE,
};

enum e_height_state
{
	HGT_NORMAL,
	HGT_CROUCH,
	HGT_PRONE,
	HGT_JUMP,
	HGT_STATES,
};

typedef struct s_player
{
	t_vec2d			map_posi;
	t_vec2d			dir_vec;
	t_vec2d			plane;
	int				pitch;
	float			angle;
	float			cos_rad;
	float			sin_rad;
	float			unit_size;
	float			forward_move;
	float			side_move;
	float			back_move;
	float			max_aim_radius;
	float			dir_len[CTR_SIZE];
	float			cur_dir_len;
	float			base_dir_len;
	float			aim_dir_len;
	float			new_fov[CTR_SIZE];
	float			cur_fov;
	float			base_fov;
	int				hgt_state;
	float			hgt_sense;
	float			cur_z;
	float			base_z;
	float			stance_z[HGT_STATES];
	bool			is_walking;
	bool			is_sprinting;
	bool			is_aiming;
	float			aim_sense;
	float			rot_sense;
	float			pitch_sense;
	float			aim_rot_multi;
	float			jump_z_mod;
	float			cur_shot_sense;
	float			cur_move_multi;
	float			move_multi[HGT_STATES];
	float			normal_move_multi;
	float			sprint_move_multi;
	float			crouch_move_multi;
	float			prone_move_multi;
	float			aim_move_multi;
	float			walk_z_mod;
	t_vec2d			(*move[16])(t_player *);
}	t_player;

//setup, render and rotation
void	player_setup(t_player *player);
void	render_player(t_win *win, t_player *player);
void	player_rotate(t_player *player);

//movement function pointers
t_vec2d	move_player_default(t_player *player);
t_vec2d	move_player_back_left(t_player *player);
t_vec2d	move_player_back_right(t_player *player);
t_vec2d	move_player_for_left(t_player *player);
t_vec2d	move_player_for_right(t_player *player);
t_vec2d	move_player_left(t_player *player);
t_vec2d	move_player_right(t_player *player);
t_vec2d	move_player_backward(t_player *player);
t_vec2d	move_player_forward(t_player *player);

#endif
