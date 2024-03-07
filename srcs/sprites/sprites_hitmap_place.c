/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_hitmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:42:16 by marvin            #+#    #+#             */
/*   Updated: 2024/02/24 10:42:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	sprite_calc_dist(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sorted[i]->status == GONE)
			game->sorted[i]->dist = FLT_MAX;
		else
			game->sorted[i]->dist \
			= fpow_2(game->player.map_posi.x - game->sorted[i]->posi.x) \
			+ fpow_2(game->player.map_posi.y - game->sorted[i]->posi.y);
		i++;
	}
}

void	door_place_hitmap(t_game *game, t_sprite *sprite)
{
	t_door	*door;

	door = (t_door *)sprite->data;
	hitlist_in_head(&game->map.hit[door->map_index], &sprite->my_hit[0]);
}

void	sprite_place_hitmap(t_game *game, t_sprite *sprite)
{
	int	map_index;

	if (sprite->type == DOOR)
		return (door_place_hitmap(game, sprite));
	if (sprite->type != ENEMY)
		return ;
	map_index = (int)(sprite->posi.x - sprite->unit_size) \
		+ (int)(sprite->posi.y - sprite->unit_size) * game->map.width;
	hitlist_in_head(&game->map.hit[map_index], &sprite->my_hit[0]);
	map_index = (int)(sprite->posi.x + sprite->unit_size) \
		+ (int)(sprite->posi.y + sprite->unit_size) * game->map.width;
	hitlist_in_head(&game->map.hit[map_index], &sprite->my_hit[1]);
	map_index = (int)(sprite->posi.x - sprite->unit_size) \
		+ (int)(sprite->posi.y + sprite->unit_size) * game->map.width;
	hitlist_in_head(&game->map.hit[map_index], &sprite->my_hit[2]);
	map_index = (int)(sprite->posi.x + sprite->unit_size) \
		+ (int)(sprite->posi.y - sprite->unit_size) * game->map.width;
	hitlist_in_head(&game->map.hit[map_index], &sprite->my_hit[3]);
}

void	setup_hitmap(t_game *game)
{
	int			i;
	t_sprite	*sprite;

	i = 0;
	while (i < game->sprite_count)
	{
		sprite = game->sorted[i];
		if (sprite->type == ENEMY || sprite->type == DOOR)
			sprite_place_hitmap(game, sprite);
		i++;
	}
}
