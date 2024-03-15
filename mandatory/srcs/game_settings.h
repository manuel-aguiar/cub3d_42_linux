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

/* player settings */

# define PLAY_UNIT_SIZE 0.2f
# define PLAY_FORWARD_MOVE_SENSE 0.003f
# define PLAY_SIDE_MOVE_SENSE 0.002f
# define PLAY_BACK_MOVE_SENSE 0.0015f
# define PLAY_SPRINT_MULTI 1.0f
# define PLAY_BASE_PITCH 0

//rotation an pitch sensibility, aiming multiplier
# define PLAY_ROT_SENSE 0.002f
# define PLAY_AIM_ROT_MULTI 0.5f

# define PLAY_HGT_NORMAL 0.5f

# define PLAY_BASE_DIR_LEN 1.0f
# define PLAY_AIM_DIR_LEN 1.5f
# define PLAY_AIM_SENSE 0.003f

# define PLAY_BASE_FOV 0.66f
# define PLAY_AIM_FOV 0.8f

//player velocity multipliers
# define PLAY_NORMAL_MOVE_MULTI 1.0f
# define PLAY_SPRINT_MOVE_MULTI 1.0f
# define PLAY_AIM_MOVE_MULTI 1.0f
# define PLAY_CROUCH_MOVE_MULTI 1.0f
# define PLAY_PRONE_MOVE_MULTI 1.0f
# define PLAY_SPRINT_ROT_MULTI 0.7f

# define PITCH_ANGLE_BASE 0
# define PITCH_ANGLE_MIN -1.0f
# define PITCH_ANGLE_MAX 1.0f
# define VERTI_SENSE 0.0002f

# define MAX_VISIBLE_DISTANCE 5.0f
# define WALL_REFLECTION 0.7f

void	settings_player(t_player *player);

#endif
