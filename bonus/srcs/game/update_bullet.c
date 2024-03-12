/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bullet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:14:44 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 15:14:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	set_hitbox(t_sprite *target, t_vec2d box[2]);
int		target_was_hit_on_z(t_game *game, t_bullet_colli *colli, \
						t_sprite *sprite, t_sprite *target);
int		friendly_bullet(t_game *game, t_bullet_colli *colli, t_sprite *sprite);

void	setup_bullet_hit(t_game *game, t_bullet_colli *colli, t_sprite *sprite)
{
	colli->bullet = (t_bullet *)sprite->data;
	colli->map_index = (int)sprite->posi.x + (int)sprite->posi.y \
		* game->map.width;
	colli->check[0] = (t_vec2d){sprite->posi.x, sprite->posi.y};
	sprite->posi.x += colli->bullet->dir.x * colli->bullet->move_sense \
		* game->player.clock->elapsed;
	sprite->posi.y += colli->bullet->dir.y * colli->bullet->move_sense \
		* game->player.clock->elapsed;
	sprite->cur_z += colli->bullet->dir.z * colli->bullet->move_sense \
		* game->player.clock->elapsed;
	colli->bullet->posi = (t_vec3d){sprite->posi.x, sprite->posi.y, \
		sprite->cur_z};
	colli->check[1] = (t_vec2d){sprite->posi.x, sprite->posi.y};
}

int	i_was_hit_on_z(t_game *game, t_bullet_colli *colli, \
		t_sprite *sprite)
{
	float	z;

	z = vec3d_get_z_from_xy(colli->bullet->posi, colli->bullet->dir, \
		colli->collision[0]);
	if (z >= game->player.jump_z_mod && z <= game->player.jump_z_mod \
		+ game->player.walk_z_mod + game->player.cur_z)
	{
		sprite->status = GONE;
		player_takes_damage(game, colli->bullet->attack_val);
		return (1);
	}
	z = vec3d_get_z_from_xy(colli->bullet->posi, colli->bullet->dir, \
		colli->collision[1]);
	if (z >= game->player.jump_z_mod && z <= game->player.jump_z_mod \
		+ game->player.walk_z_mod + game->player.cur_z)
	{
		sprite->status = GONE;
		player_takes_damage(game, colli->bullet->attack_val);
		return (1);
	}
	return (0);
}

int	enemy_bullet_hit_door(t_game *game, t_bullet_colli *colli, \
							t_sprite *sprite)
{
	t_sprite		*target;
	t_hitnode		*node;

	node = game->map.hit[colli->map_index].head;
	while (node)
	{
		target = node->sprite;
		if (target->type == DOOR)
		{
			set_hitbox(target, colli->box);
			if (liang_barsky_hit(colli->box, colli->check, colli->collision) \
			&& target_was_hit_on_z(game, colli, sprite, target))
				return (1);
		}
		node = node->next;
	}
	return (0);
}

int	enemy_bullet(t_game *game, t_bullet_colli *colli, t_sprite *sprite)
{
	if (enemy_bullet_hit_door(game, colli, sprite))
		return (0);
	if (ft_abs(game->player.map_posi.x - (int)colli->check[0].x) > 1 \
	&& ft_abs(game->player.map_posi.y - (int)colli->check[0].y) > 1)
		return (0);
	colli->box[0] = (t_vec2d){game->player.map_posi.x \
		- game->player.unit_size, game->player.map_posi.y \
		- game->player.unit_size};
	colli->box[1] = (t_vec2d){game->player.map_posi.x \
		+ game->player.unit_size, game->player.map_posi.y \
		+ game->player.unit_size};
	if (liang_barsky_hit(colli->box, colli->check, colli->collision) \
	&& i_was_hit_on_z(game, colli, sprite))
		return (1);
	return (0);
}

void	update_bullet(t_game *game, t_sprite *sprite)
{
	t_bullet_colli	colli;
	t_vec3d			sub;
	float			dot;

	if (sprite->status == ON_WALL || sprite->status == ON_CEIL)
		return ;
	setup_bullet_hit(game, &colli, sprite);
	if ((colli.bullet->shooter == B_ME \
	&& friendly_bullet(game, &colli, sprite)) || \
	(colli.bullet->shooter == B_ENEMY \
	&& enemy_bullet(game, &colli, sprite)))
		return ;
	sub = vec3d_sub(colli.bullet->posi, colli.bullet->hole);
	dot = sub.x * colli.bullet->dir.x + sub.y * colli.bullet->dir.y \
		+ sub.z * colli.bullet->dir.z;
	if (dot <= 0)
	{
		sprite->status = ON_WALL;
		if (colli.bullet->wall_hole == false)
		{
			sprite->status = ON_CEIL;
			sprite->cur_z = float_clamp(sprite->cur_z, 0.0f, 1.0f);
		}
		sprite->tex = WALL_BULLET_TEX;
	}
}
