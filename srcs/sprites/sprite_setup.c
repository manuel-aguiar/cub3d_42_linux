/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriteibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:25:46 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 10:25:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	extract_sprites(t_game *game, t_map *map)
{
	int	i;
	int	cur;

	i = 0;
	cur = 0;
	while (cur < game->sprite_count)
	{
		while (!char_in_charset(map->map[i], SPRITES))
			i++;
		if ((map->map[i] == MAP_MEDI && !extract_medi(game, map, cur, i)) \
		|| (map->map[i] == MAP_AMMO && !extract_ammo(game, map, cur, i)) \
		|| (map->map[i] == MAP_DOOR && !extract_door(game, map, cur, i)) \
		|| (map->map[i] == MAP_X_ENEMY && !extract_x_enemy(game, map, cur, i)) \
		|| (map->map[i] == MAP_Y_ENEMY && !extract_y_enemy(game, map, cur, i)) \
		|| (map->map[i] == MAP_Z_ENEMY && !extract_z_enemy(game, map, cur, i)))
			return (0);
		i++;
		cur++;
	}
	return (1);
}

int	place_bullet(t_game *game, int place)
{
	t_bullet	*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_bullet, sizeof(*data));
	sprite->data = data;
	sprite->type = BULLET;
	sprite->status = GONE;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->unit_size = data->unit_size;
	sprite->dist = FLT_MAX;
	sprite->tex = MY_BULLET_TEX;
	return (1);
}

int	fill_with_bullets(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->max_bullets)
	{
		if (!place_bullet(game, game->sprite_count + i))
			return (0);
		i++;
	}
	return (1);
}

void	fill_sorted_pointers(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->sprite_count)
	{
		game->sorted[i] = &game->sprites[i];
		i++;
	}
}

int	setup_sprites(t_game *game)
{
	t_sprite	*sprite;
	t_map		*map;
	int			count;
	int			i;

	map = &game->map;
	i = 0;
	count = 0;
	while (i < map->len)
	{
		if (char_in_charset(map->map[i], SPRITES))
			count++;
		i++;
	}
	sprite = malloc(sizeof(*sprite) * (count + game->max_bullets));
	if (!sprite)
		return (perror_msg_int("malloc", 0));
	game->sprites = sprite;
	game->sprite_count = count;
	if (!extract_sprites(game, map))
		return (0);
	if (!fill_with_bullets(game))
		return (0);
	game->sprite_count += game->max_bullets;
	game->sorted = malloc(sizeof(*game->sorted) * game->sprite_count);
	if (!game->sorted)
		return (perror_msg_int("malloc", 0));
	fill_sorted_pointers(game);
	return (1);
}
