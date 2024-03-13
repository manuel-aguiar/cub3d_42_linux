/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:43:49 by marvin            #+#    #+#             */
/*   Updated: 2024/01/29 19:43:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_SETTINGS_H

# define GAME_SETTINGS_H

# include "game.h"

/* window settings */
# define MAX_WIN_WIDTH 1920
# define MIN_WIN_WIDTH 800
# define MAX_WIN_HEIGHT 1080
# define MIN_WIN_HEIGHT 480

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define WIN_NAME "Cub3d\0"

# define RGB_SIZE 4

# define WIN_MIN_SIGMA 1
# define WIN_MAX_SIGMA 50
# define WIN_PAUSE_TIME 500

/* compass settings */

# define COMP_MAX_RAD 300
# define COMP_MIN_RAD 50
# define COMP_INNER_RAD_PERC 0.8f
# define COMP_LETTER_RAD_PERC 0.9f

# define COMP_LETTER_HGT_PERC 0.1f
# define COMP_LETTER_WDT_PERC 0.05f

/* compass squares */
# define SQR_MAX_HEIGHT_PERC 0.5f
# define SQR_MIN_HEIGHT_PERC 0.005f
# define SQR_HEIGHT_PERC 0.2f
# define COMP_PLAY_RAD 0.2f

/* player settings */

# define PLAYER_HEALTH 100
# define PLAYER_AMMO 100
# define PLAYER_ATTACK_VAL 10

# define PLAY_UNIT_SIZE 0.2f
# define PLAY_FORWARD_MOVE_SENSE 0.0022f  //0.003f
# define PLAY_SIDE_MOVE_SENSE 0.0013f		//0.0018f
# define PLAY_BACK_MOVE_SENSE 0.0008f		//0.0008f
# define PLAY_SPRINT_MULTI 1.5f
# define PLAY_BASE_PITCH 0

//rotation an pitch sensibility, aiming multiplier
# define PLAY_ROT_SENSE 0.0002f
# define PLAY_PITCH_SENSE 0.0002f
# define PLAY_AIM_ROT_MULTI 0.5f

# define PLAY_HGT_NORMAL 0.5f
# define PLAY_HGT_PRONE 0.1f
# define PLAY_HGT_CROUCH 0.3f
# define PLAY_HGT_SENSE 0.001f

# define PLAY_BASE_DIR_LEN 1.0f
# define PLAY_AIM_DIR_LEN 1.5f
# define PLAY_AIM_SENSE 0.003f

# define PLAY_BASE_FOV 0.66f
# define PLAY_AIM_FOV 0.8f

//player jump characteristics
# define PLAY_JUMP_INIT 0.0019f
# define PLAY_JUMP_INC 0.00001f
# define PLAY_JUMP_PRESS_CAP 0.007f
# define PLAY_JUMP_RELEASE_CAP 0.002f
# define PLAY_VERTICAL_GRAVITY 0.000005f

//player walking
# define PLAY_WALKING_GRAVITY 0.000005f
# define PLAY_WALK_RADIUS	0.04f
# define PLAY_CROUCH_RADIUS 0.015f
# define PLAY_PRONE_RADIUS 0.005f

//player velocity multipliers
# define PLAY_NORMAL_MOVE_MULTI 1.0f
# define PLAY_SPRINT_MOVE_MULTI 2.0f
# define PLAY_AIM_MOVE_MULTI 0.5f
# define PLAY_CROUCH_MOVE_MULTI 0.5f
# define PLAY_PRONE_MOVE_MULTI 0.2f
# define PLAY_SPRINT_ROT_MULTI 0.7f

# define PITCH_ANGLE_BASE 0
# define PITCH_ANGLE_MIN -1.0f
# define PITCH_ANGLE_MAX 1.0f
# define VERTI_SENSE 0.0002f

# define MAX_VISIBLE_DISTANCE 5.0f

# define PLAY_HEALTH_MIN 0
# define PLAY_HEALTH_MAX 100
# define PLAY_HEALTH_START 70
# define PLAY_AMMO_MIN 0
# define PLAY_AMMO_MAX 200
# define PLAY_AMMO_START 150
# define PLAY_BULLET_DAMAGE 10

# define PLAY_SHOT_MIN_TIME 100
# define PLAY_SHOT_INIT 0.0022f
# define PLAY_SHOT_GRAVITY 0.00003f

//sprite settings
# define GAME_FLOAT_SENSE 0.003f

//X enemy default stats
# define X_ENEMY_HGT 0.5f
# define X_ENEMY_WDT 3.0f
# define X_ENEMY_Z 0.0f
# define X_ENEMY_UNIT 0.2f
# define X_ENEMY_Z_SENSE 0.005f
# define X_ENEMY_MOVE_SENSE 0.0015f
# define X_ENEMY_MS_SWAP 500
# define X_ENEMY_ATTACK 20
# define X_ENEMY_HEALTH 50
# define X_ENEMY_TIME_ATTACK 1000

// Y enemy default stats
# define Y_ENEMY_HGT 0.7f
# define Y_ENEMY_WDT 3.0f
# define Y_ENEMY_Z 0.0f
# define Y_ENEMY_UNIT 0.3f
# define Y_ENEMY_Z_SENSE 0.003f
# define Y_ENEMY_MOVE_SENSE 0.0010f
# define Y_ENEMY_MS_SWAP 500
# define Y_ENEMY_ATTACK 30
# define Y_ENEMY_HEALTH 70
# define Y_ENEMY_TIME_ATTACK 1000

// Z enemy default stats
# define Z_ENEMY_HGT 0.5f
# define Z_ENEMY_WDT 3.0f
# define Z_ENEMY_Z 0.0f
# define Z_ENEMY_UNIT 0.2f
# define Z_ENEMY_Z_SENSE 0.005f
# define Z_ENEMY_MOVE_SENSE 0.0015f
# define Z_ENEMY_MS_SWAP 500
# define Z_ENEMY_ATTACK 30
# define Z_ENEMY_HEALTH 50
# define Z_ENEMY_TIME_ATTACK 1000
# define Z_ENEMY_SHOT_MAX_TIME 2000

// DOOR default stats
# define DOOR_HGT 1.0f
# define DOOR_WDT 0.3f
# define DOOR_Z 0.0f
# define DOOR_UNIT 0.2f
# define DOOR_MOVE_SENSE 0.002f
# define DOOR_DIST_SENSE 1.5f

// MEDIKIT default stats
# define MEDI_HGT 0.5f
# define MEDI_WDT 0.5f
# define MEDI_Z 0.2f
# define MEDI_UNIT 0.2f
# define MEDI_Z_SENSE 100
# define MEDI_RESOURCE 20
# define MEDI_FLOAT_RADIUS 0.1f

// AMMO POUCH default stats
# define AMMO_HGT 0.3f
# define AMMO_WDT 0.8f
# define AMMO_Z 0.15f
# define AMMO_UNIT 0.2f
# define AMMO_Z_SENSE 0.005f
# define AMMO_RESOURCE 20
# define AMMO_FLOAT_RADIUS 0.1f

// blur limits
# define BLUR_KERNEL_MAX 31
# define BLUR_KERNEL_SIZE 17
# define BLUR_KERNEL_SIGMA 7

# define BLUR_ON true

# define GAME_WALL_REFLECTION 0.5f

# define MAX_BULLETS 100

//bullet default stats
# define BULLET_MOVE_SENSE 0.008f
# define BULLET_HGT 0.1f
# define BULLET_UNIT_SIZE 0.05f
# define BULLET_BASE_Z 0.0f

# define GAME_WIN_TIME 4000
# define GAME_LOST_TIME 4000

void	settings_template_door(t_door *door);
void	settings_template_ammo(t_ammo *ammo);
void	settings_template_enemy(t_enemy *enemy);
void	settings_template_medi(t_medi *medi);
void	settings_template_bullet(t_bullet *bullet);
void	settings_template_x_enemy(t_enemy *enemy);
void	settings_template_y_enemy(t_enemy *enemy);
void	settings_template_z_enemy(t_enemy *enemy);
void	settings_player(t_player *player);
void	settings_all_templates(t_game *game);

#endif
