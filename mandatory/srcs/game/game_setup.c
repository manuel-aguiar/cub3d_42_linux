/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GAME.C                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:51:29 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 10:51:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	setup_all_angles(t_game *game, float rad)
{
	game->player.angle = radian_truncate(rad);
	game->player.cos_rad = cosf(game->player.angle);
	game->player.sin_rad = sinf(game->player.angle);
	game->player.dir_vec = (t_vec2d){game->player.cos_rad, \
		game->player.sin_rad};
	game->player.plane = vec2d_multi((t_vec2d){game->player.sin_rad, \
		- game->player.cos_rad}, game->player.cur_fov);
}

void	game_starting_angle(t_game *game, char direction)
{
	if (direction == MAP_NORTH)
		setup_all_angles(game, P_MY_PI / 2);
	if (direction == MAP_SOUTH)
		setup_all_angles(game, -P_MY_PI / 2);
	if (direction == MAP_EAST)
		setup_all_angles(game, 0);
	if (direction == MAP_WEST)
		setup_all_angles(game, P_MY_PI);
}

void	game_find_player_set_angles(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.len)
	{
		if (char_in_charset(game->map.map[i], VALID_DIR_CHARS))
			break ;
		i++;
	}
	game->player.map_posi.x = (float)map_col(&game->map, i) + 0.5f;
	game->player.map_posi.y = (float)map_row(&game->map, i) + 0.5f;
	game_starting_angle(game, game->map.map[i]);
}

int	game_start(t_game *game, char *game_config)
{
	*game = (t_game){};
	apply_all_settings(game);
	if (!map_parsing(&game->map, game_config))
		return (0);
	game_find_player_set_angles(game);
	player_setup(&game->player);
	game->hori_rays = malloc(sizeof(*game->hori_rays) \
		* game->win.width);
	game->verti_rays = malloc(sizeof(*game->verti_rays) \
		* game->win.height);
	if (!game->hori_rays || !game->verti_rays)
		return (perror_msg_int("malloc", 0));
	if (!win_init_window(&game->win) || !game_load_textures(game))
		return (0);
	return (1);
}
