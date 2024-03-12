/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:13:02 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 15:13:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	enemy_sees_player(t_game *game, t_sprite *sprite, t_vec2d dir);

void	z_enemy_shoot(t_game *game, t_sprite *sprite, t_enemy *enemy)
{
	enemy->cur_shot_time += game->clock.elapsed;
	if (enemy->cur_shot_time >= enemy->shot_this_time)
	{
		start_enemy_bullet(game, sprite);
		enemy->cur_shot_time = 0;
		enemy->shot_this_time = rand_int(0, enemy->shot_max_time);
	}
}

void	enemy_movement(t_game *game, t_sprite *sprite, t_enemy *enemy)
{
	t_vec2d	dir;
	float	dir_len;

	dir = (t_vec2d){sprite->posi.x - game->player.map_posi.x, \
		sprite->posi.y - game->player.map_posi.y};
	dir_len = vec2d_len(dir);
	if (dir_len < sprite->unit_size + game->player.unit_size)
		return ;
	dir = vec2d_norm(dir, dir_len);
	if (enemy_sees_player(game, sprite, dir))
	{
		dir = vec2d_multi(vec2d_multi(dir, enemy->move_sense \
			* game->player.clock->elapsed), -1);
		handle_collisions(game, &sprite->posi, dir, sprite->unit_size);
		if (enemy->type == Z_ENEMY)
			z_enemy_shoot(game, sprite, enemy);
	}
	else
		enemy->cur_shot_time = 0;
}

void	player_takes_damage(t_game *game, int damage)
{
	game->player.health[CTR_CUR] \
		= ft_max(game->player.health[CTR_CUR] - damage, 0);
	if (game->player.health[CTR_CUR] == 0)
		game->is_lost = true;
}

void	update_enemy(t_game *game, t_sprite *sprite)
{
	t_enemy	*enemy;

	enemy = (t_enemy *)sprite->data;
	if (enemy->health <= 0)
	{
		sprite->status = GONE;
		return ;
	}
	enemy->elapsed += game->player.clock->elapsed;
	if (enemy->elapsed >= enemy->ms_to_swap)
	{
		sprite->inverted = !sprite->inverted;
		enemy->elapsed = rand_int(0, enemy->ms_to_swap);
	}
	if (enemy->attack_elapsed != -1)
		enemy->attack_elapsed += game->player.clock->elapsed;
	if (enemy->attack_elapsed >= enemy->attack_time)
		enemy->attack_elapsed = -1;
	if (sprite->dist <= game->player.unit_size + sprite->unit_size \
	&& enemy->attack_elapsed == -1)
	{
		player_takes_damage(game, enemy->attack_val);
		enemy->attack_elapsed = 0;
	}
	enemy_movement(game, sprite, enemy);
}
