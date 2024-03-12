/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_updates.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:55:22 by codespace         #+#    #+#             */
/*   Updated: 2024/03/12 20:10:58 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	update_this_sprite(t_game *game, int i)
{
	if (game->sorted[i]->status != GONE)
	{
		if (game->sorted[i]->type == DOOR)
			update_door(game, game->sorted[i]);
		if (game->sorted[i]->type == ENEMY)
			update_enemy(game, game->sorted[i]);
		if (game->sorted[i]->type == MEDIKIT)
			update_medikit(game, game->sorted[i]);
		if (game->sorted[i]->type == AMMOKIT)
			update_ammokit(game, game->sorted[i]);
		sprite_place_hitmap(game, game->sorted[i]);
	}
}

void	update_sprites(t_game *game)
{
	int	i;

	clean_hitmap(game);
	sprite_calc_dist(game);
	sprite_qs_distance(game->sorted, game->sprite_count, sprite_qs_comp);
	game->floating += game->float_sense * game->player.clock->elapsed;
	game->float_sin = sinf(game->floating);
	if (game->floating > 2 * MY_PI)
		game->floating -= 2 * MY_PI;
	i = 0;
	while (i < game->sprite_count)
	{
		update_this_sprite(game, i);
		i++;
	}
	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sorted[i]->type == BULLET && game->sorted[i]->status != GONE)
			update_bullet(game, game->sorted[i]);
		i++;
	}
}

int	game_is_paused(t_game *game)
{
	if ((game->win.keys >> BIT_PAUSE_T) & 1 \
		|| (!((game->win.keys >> BIT_PAUSE_T) & 1) \
		&& game->win.blur.elapsed > 0) \
		|| game->is_lost)
		return (1);
	return (0);
}

void	game_actions(t_game *game)
{
	if ((game->win.keys >> BIT_ESC) & 1)
		free_game(game);
	update_clock(&game->clock);
	if (game_is_paused(game))
		return ;
	update_sprites(game);
	game_key_manager(game);
	game_mouse_manager(game);
	player_actions(game);
	mlx_mouse_move(game->win.mlx, game->win.mlx_win, \
		game->win.width / 2, game->win.height / 2);
}
