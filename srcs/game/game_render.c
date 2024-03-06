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
	&& game->win.blur.elapsed > 0)
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
	mlx_mouse_move(game->win.mlx, game->win.mlx_win, game->win.width / 2, game->win.height / 2);
}

int	game_render(t_game *game)
{
	int blur_on;

	game_actions(game);
	blur_on = (game->win.keys >> BIT_BLUR_T) & 1;
	if ((game->win.keys >> BIT_PAUSE_T) & 0xff)
		window_pause_manager(&game->win, PAUSE_ON, blur_on, pause_text_string);
	else if (game->win.blur.elapsed > 0)
		window_pause_manager(&game->win, PAUSE_OFF, blur_on, pause_text_string);
	else if (game->is_lost)
	{
		if (game->cur_time_lost_str >= game->total_time_lost_str)
			free_game(game);
		else
		{
			game->cur_time_lost_str += game->clock.elapsed;
			window_pause_manager(&game->win, PAUSE_ON, blur_on, you_lost_text_string);
		}
	}
	else
	{
		ft_memset(game->win.front_buf.pixels, 0, game->win.width * game->win.height * game->win.rgb_size);
		hori_raycasting(game);
		floorcast(game);
		sprite_cast(game);
		game->compass.blur_on = blur_on;
		//if (((game->win.keys) >> BIT_HUD_T) & 1)
		//{
		//	render_compass(&game->win, &game->compass);
		//	render_map_inside_compass(game);
		//	render_player_inside_compass(game);
		//	render_stats_bars(game);
		//}
	}
	game->win.set_pixel(&game->win, game->win.width / 2, game->win.height / 2, (unsigned int)-1);
	if (game->enemy_count == 0 && game->cur_time_win_str < game->total_time_win_str)
	{
		game->cur_time_win_str += game->clock.elapsed;
		enemies_defeated_text_string(&game->win);
	}
	mlx_put_image_to_window(game->win.mlx, game->win.mlx_win, game->win.front_buf.img, 0, 0);
	return (1);
}
