/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:37:43 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 12:37:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void		update_sprites(t_game *game)
{
	int i;

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
		if (game->sorted[i]->status != GONE)
		{
			if (game->sorted[i]->type == BULLET)
				update_bullet(game, game->sorted[i]);
			if (game->sorted[i]->type == DOOR)
				update_door(game, game->sorted[i]);
			if (game->sorted[i]->type == ENEMY)
				update_enemy(game, game->sorted[i]);
			if (game->sorted[i]->type == MEDIKIT)
				update_medikit(game, game->sorted[i]);
			if (game->sorted[i]->type == AMMOKIT)
				update_ammokit(game, game->sorted[i]);
			if (game->sorted[i]->status != GONE)
				sprite_place_hitmap(game, game->sorted[i]);			
		}
		i++;
	}
}

int	game_is_paused(t_game *game)
{
	if ((*(game->keys) >> BIT_PAUSE_T) & 1 \
	|| (!((*(game->keys) >> BIT_PAUSE_T) & 1) \
	&& game->win.blur.elapsed > 0))
		return (1);
	return (0);
}

void	game_actions(t_game *game)
{
	update_clock(&game->clock);
	if (game_is_paused(game))
		return ;
	update_sprites(game);
	game_key_manager(game);
	game_mouse_manager(game);
	player_actions(game);
}

void	game_render(t_game *game)
{
	if ((*(game->keys) >> BIT_PAUSE_T) & 0xff)
		window_pause_manager(&game->win, PAUSE_ON, (*(game->keys) >> BIT_BLUR_T) & 1);
	else if (game->win.blur.elapsed > 0)
		window_pause_manager(&game->win, PAUSE_OFF, (*(game->keys) >> BIT_BLUR_T) & 1);
	else
	{
		hori_raycasting(game);
		floorcast(game);
		sprite_cast(game);
		game->compass.blur_on = (*(game->keys) >> BIT_BLUR_T) & 1;
		if (((*game->keys) >> BIT_HUD_T) & 1)
		{
			render_compass(&game->win, &game->compass);
			render_map_inside_compass(game);
			render_player_inside_compass(game);
			render_stats_bars(game);
		}
	}
	game->win.set_pixel(&game->win, game->win.width / 2, game->win.height / 2, (unsigned int)-1);
}