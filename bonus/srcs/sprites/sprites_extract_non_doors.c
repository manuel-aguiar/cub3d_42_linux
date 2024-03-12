/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_extract_non_doors.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:46:23 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:46:23 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	extract_x_enemy(t_game *game, t_map *map, int place, int map_index)
{
	t_enemy		*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_x_enemy, sizeof(*data));
	sprite->data = data;
	sprite->type = ENEMY;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	data->elapsed = rand_int(0, data->ms_to_swap);
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->tex = X_ENEMY_TEX;
	game->enemy_count++;
	return (1);
}

int	extract_y_enemy(t_game *game, t_map *map, int place, int map_index)
{
	t_enemy		*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_y_enemy, sizeof(*data));
	sprite->data = data;
	sprite->type = ENEMY;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	data->elapsed = rand_int(0, data->ms_to_swap);
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->tex = Y_ENEMY_TEX;
	game->enemy_count++;
	return (1);
}

int	extract_z_enemy(t_game *game, t_map *map, int place, int map_index)
{
	t_enemy		*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_z_enemy, sizeof(*data));
	sprite->data = data;
	sprite->type = ENEMY;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	data->elapsed = rand_int(0, data->ms_to_swap);
	sprite->cur_z = rand_float(0.0f, 1.0f - data->height);
	data->shot_this_time = rand_int(0, data->shot_max_time);
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->tex = Z_ENEMY_TEX;
	game->enemy_count++;
	return (1);
}

int	extract_ammo(t_game *game, t_map *map, int place, int map_index)
{
	t_ammo		*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_ammo, sizeof(*data));
	sprite->data = data;
	sprite->type = AMMOKIT;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->tex = AMMO_TEX;
	return (1);
}

int	extract_medi(t_game *game, t_map *map, int place, int map_index)
{
	t_medi		*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_medi, sizeof(*data));
	sprite->data = data;
	sprite->type = MEDIKIT;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->tex = MEDI_TEX;
	return (1);
}
