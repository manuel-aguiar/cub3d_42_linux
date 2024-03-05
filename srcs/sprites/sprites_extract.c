/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_medi_ammo_enemy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:32:10 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 15:32:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	extract_enemy(t_game *game, t_map *map, int place, int map_index)
{
	t_enemy		*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_enemy, sizeof(*data));
	sprite->data = data;
	sprite->type = ENEMY;
	sprite->status = NOT_VIS;
	sprite->inverted = false;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	data->elapsed = rand_int(&game->rand, 0, data->ms_to_swap);
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->dist = FLT_MAX;
	sprite->tex = ENEMY_TEX;
	game->enemy_count++;
	return (1);
}

int	extract_ammo(t_game *game, t_map *map, int place, int map_index)
{
	t_ammo		*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_ammo, sizeof(*data));
	sprite->data = data;
	sprite->type = AMMOKIT;
	sprite->status = NOT_VIS;
	sprite->inverted = false;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->dist = FLT_MAX;
	sprite->tex = AMMO_TEX;
	return (1);
}

int	extract_medi(t_game *game, t_map *map, int place, int map_index)
{
	t_medi		*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_medi, sizeof(*data));
	sprite->data = data;
	sprite->type = MEDIKIT;
	sprite->status = NOT_VIS;
	sprite->inverted = false;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->dist = FLT_MAX;
	sprite->tex = MEDI_TEX;
	return (1);
}

int	check_door_orient(t_map *map, t_door *door, \
	t_sprite *sprite, int map_index)
{
	map->doors[map_index] = sprite;
	if (map->map[map_index + 1] == MAP_WALL \
	&& map->map[map_index - 1] == MAP_WALL \
	&& map->map[map_index + map->width] != MAP_WALL \
	&& map->map[map_index - map->width] != MAP_WALL)
		door->orient = NS;
	else if (map->map[map_index + 1] != MAP_WALL \
	&& map->map[map_index - 1] != MAP_WALL \
	&& map->map[map_index + map->width] == MAP_WALL \
	&& map->map[map_index - map->width] == MAP_WALL)
		door->orient = WE;
	else
		return (error_msg_int("cub3d: doors are missplaced\n", \
			STDERR_FILENO, 0));
	door->base_position = sprite->posi;
	return (1);
}

int			extract_door(t_game *game, t_map *map, int place, int map_index)
{
	t_door 		*data;
	t_sprite 	*sprite;

	sprite = &game->sprites[place];
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_door, sizeof(*data));
	data->map_index = map_index;
	sprite->data = data;
	sprite->type = DOOR;
	sprite->status = NOT_VIS;
	sprite->inverted = false;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->unit_size = 0.5f;
	sprite->width = 0;
	sprite->dist = FLT_MAX;
	sprite->tex = DOOR_TEX;
	if(!check_door_orient(map, data, sprite, map_index))
		return (0);
	return (1);
}
