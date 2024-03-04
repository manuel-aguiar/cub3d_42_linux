/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager_mouse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:52:57 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 13:52:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	start_new_bullet(t_game *game)
{
	t_sprite	*sprite;
	t_bullet	*bullet;

	if (game->live_bullets == game->max_bullets)
		game->live_bullets = 0;
	sprite = &game->sprites[game->sprite_count - game->max_bullets \
		+ game->live_bullets];
	bullet = (t_bullet *)sprite->data;
	bullet->dir = game->player.dir_3d;
	sprite->posi = vec2d_add(game->player.map_posi, \
		vec2d_multi(game->player.dir_vec, game->player.unit_size * 2));
	sprite->cur_z = (game->player.cur_z + game->player.jump_z_mod + \
		game->player.walk_z_mod + bullet->base_z) + bullet->dir.z \
			* game->player.unit_size * 2;
	sprite->status = VISIBLE;
	bullet->posi = (t_vec3d){sprite->posi.x, sprite->posi.y, sprite->cur_z};
	bullet->hole = bullet_rest(game, bullet);
	game->live_bullets++;
}

void	game_mouse_manager(t_game *game)
{
	game->player.is_aiming = ((game->win.mouse.buttons >> BIT_AIM) & 1);
	if (((game->win.mouse.buttons >> BIT_SHOOT) & 1))
	{
		if (game->player.ammo[CTR_CUR] > 0)
		{
			start_new_bullet(game);
			game->player.ammo[CTR_CUR]--;
			game->player.cur_shot_sense = game->player.shot_init;
		}
		game->win.mouse.buttons &= ~(1 << BIT_SHOOT);
	}
}
