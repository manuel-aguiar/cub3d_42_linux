/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:24:02 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 15:24:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	close_door(t_game *game, t_sprite *sprite, t_door *door)
{
	if (door->orient == NS)
		sprite->posi.x = float_clamp(sprite->posi.x + door->move_sense \
			* game->player.clock->elapsed, door->base_position.x - 1.0f, \
			door->base_position.x);
	else
		sprite->posi.y = float_clamp(sprite->posi.y + door->move_sense \
			* game->player.clock->elapsed, door->base_position.y - 1.0f, \
			door->base_position.y);
}

static inline void	open_door(t_game *game, t_sprite *sprite, t_door *door)
{
	if (door->orient == NS)
		sprite->posi.x = float_clamp(sprite->posi.x - door->move_sense \
			* game->player.clock->elapsed, door->base_position.x - 1.0f, \
			door->base_position.x);
	else
		sprite->posi.y = float_clamp(sprite->posi.y - door->move_sense \
			* game->player.clock->elapsed, door->base_position.y - 1.0f, \
			door->base_position.y);
}

void	update_door(t_game *game, t_sprite *sprite)
{
	t_door	*door;
	float	dist;

	door = (t_door *)sprite->data;
	dist = fpow_2(game->player.map_posi.x - door->base_position.x) \
		+ fpow_2(game->player.map_posi.y - door->base_position.y);
	door->state = DOOR_CLOSED;
	if (dist < door->dist_sense)
		open_door(game, sprite, door);
	else
		close_door(game, sprite, door);
	if (door->orient == NS && door->base_position.x - sprite->posi.x == 1.0f)
		door->state = DOOR_OPEN;
	if (door->orient == WE && door->base_position.y - sprite->posi.y == 1.0f)
		door->state = DOOR_OPEN;
}
