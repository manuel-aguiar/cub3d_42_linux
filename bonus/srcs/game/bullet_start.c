/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:31:56 by codespace         #+#    #+#             */
/*   Updated: 2024/03/12 19:41:49 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	start_friendly_bullet(t_game *game)
{
	t_sprite	*sprite;
	t_bullet	*bullet;

	if (game->live_bullets == game->max_bullets)
		game->live_bullets = 0;
	sprite = &game->sprites[game->sprite_count - game->max_bullets \
		+ game->live_bullets];
	sprite->tex = MY_BULLET_TEX;
	sprite->posi = game->player.map_posi;
	handle_collisions(game, &sprite->posi, \
		vec2d_multi(game->player.dir_vec, game->player.unit_size * 2), \
		sprite->unit_size);
	sprite->status = VISIBLE;
	bullet = (t_bullet *)sprite->data;
	bullet->shooter = B_ME;
	bullet->dir = game->player.dir_3d;
	sprite->cur_z = (game->player.cur_z + game->player.jump_z_mod + \
		game->player.walk_z_mod + bullet->base_z) + bullet->dir.z \
			* vec2d_len(vec2d_sub(sprite->posi, game->player.map_posi));
	bullet->posi = (t_vec3d){sprite->posi.x, sprite->posi.y, sprite->cur_z};
	bullet->wall_hole = true;
	bullet->hole = bullet_rest(game, bullet);
	bullet->move_sense = game->template_bullet.move_sense;
	bullet->attack_val = game->template_bullet.attack_val / 3;
	game->live_bullets++;
}

void	start_enemy_bullet(t_game *game, t_sprite *enemy)
{
	t_sprite	*sprite;
	t_bullet	*bullet;
	t_vec3d		dir;

	if (game->live_bullets == game->max_bullets)
		game->live_bullets = 0;
	sprite = &game->sprites[game->sprite_count - game->max_bullets \
		+ game->live_bullets];
	sprite->status = VISIBLE;
	sprite->posi = enemy->posi;
	sprite->tex = EN_BULLET_TEX;
	sprite->cur_z = (enemy->cur_z + enemy->height / 2);
	dir = (t_vec3d){game->player.map_posi.x - sprite->posi.x, \
	game->player.map_posi.y - sprite->posi.y, game->player.cur_z \
	+ game->player.jump_z_mod + game->player.walk_z_mod - sprite->cur_z};
	dir = vec3d_norm(dir, vec3d_len(dir));
	bullet = (t_bullet *)sprite->data;
	bullet->dir = dir;
	bullet->shooter = B_ENEMY;
	bullet->posi = (t_vec3d){sprite->posi.x, sprite->posi.y, sprite->cur_z};
	bullet->wall_hole = true;
	bullet->hole = bullet_rest(game, bullet);
	bullet->move_sense = game->template_bullet.move_sense / 3;
	game->live_bullets++;
}
