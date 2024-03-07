/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpcast_orientation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:13:43 by marvin            #+#    #+#             */
/*   Updated: 2024/03/07 13:41:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	door_orientation(t_game *game, t_sprite *sprite, \
	t_interp_cast *cast)
{
	if (cast->door->orient == NS)
	{
		cast->inverted = false;
		cast->start.point = (t_vec2d){sprite->posi.x - 0.5f, sprite->posi.y};
		cast->end.point = (t_vec2d){sprite->posi.x + 0.5f, sprite->posi.y};
	}
	else
	{
		cast->inverted = true;
		cast->start.point = (t_vec2d){sprite->posi.x, sprite->posi.y - 0.5f};
		cast->end.point = (t_vec2d){sprite->posi.x, sprite->posi.y + 0.5f};
	}
	if ((cast->door->orient == NS \
	&& game->player.map_posi.y > cast->start.point.y) \
	|| (cast->door->orient == WE \
	&& game->player.map_posi.x > cast->start.point.x))
	{
		vec2d_swap(&cast->start.point, &cast->end.point);
		cast->inverted = !cast->inverted;
	}
}

static inline void	bullet_orientation(t_game *game, t_sprite *sprite, \
	t_interp_cast *cast)
{
	bool	ns;

	ns = (cast->bullet->hole.y == (int)cast->bullet->hole.y);
	if (ns)
	{
		cast->inverted = false;
		cast->start.point = (t_vec2d){sprite->posi.x - sprite->unit_size, \
			sprite->posi.y};
		cast->end.point = (t_vec2d){sprite->posi.x + sprite->unit_size, \
			sprite->posi.y};
	}
	else
	{
		cast->inverted = true;
		cast->start.point = (t_vec2d){sprite->posi.x, sprite->posi.y \
			- sprite->unit_size};
		cast->end.point = (t_vec2d){sprite->posi.x, sprite->posi.y \
			+ sprite->unit_size};
	}
	if ((ns && game->player.map_posi.y > cast->start.point.y) \
	|| (!ns && game->player.map_posi.x > cast->start.point.x))
	{
		vec2d_swap(&cast->start.point, &cast->end.point);
		cast->inverted = !cast->inverted;
	}
}

void	setup_orientation(t_game *game, t_sprite *sprite, t_interp_cast *cast)
{
	if (sprite->type == DOOR)
	{
		cast->door = (t_door *)sprite->data;
		cast->tex = &game->tex[DOOR_TEX];
		door_orientation(game, sprite, cast);
	}
	else if (sprite->type == BULLET)
	{
		cast->bullet = (t_bullet *)sprite->data;
		cast->tex = &game->tex[WALL_BULLET_TEX];
		bullet_orientation(game, sprite, cast);
	}
}
