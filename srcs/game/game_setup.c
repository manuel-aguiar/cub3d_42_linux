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

# include "game.h"

void	setup_all_angles(t_game *game, float rad)
{
	game->player.angle = radian_truncate(rad);
	game->compass.angle = radian_truncate(-game->player.angle);
	game->player.cos_rad = cosf(game->player.angle);
	game->player.sin_rad = sinf(game->player.angle);
	game->compass.cos_rad = game->player.cos_rad;
	game->compass.sin_rad = -game->player.sin_rad;
	game->player.dir_vec = (t_vec2d){game->player.cos_rad, game->player.sin_rad};
	game->player.plane = vec2d_multi((t_vec2d){game->player.sin_rad, \
		- game->player.cos_rad}, game->player.cur_fov);
}

void		game_starting_angle(t_game *game, char direction)
{
	if (direction == MAP_NORTH)
		setup_all_angles(game, P_MY_PI / 2); 
	if (direction == MAP_SOUTH)
		setup_all_angles(game, - P_MY_PI / 2);
	if (direction == MAP_EAST)
		setup_all_angles(game, 0);
	if (direction == MAP_WEST)
		setup_all_angles(game, P_MY_PI);
}


void		game_find_player_set_angles(t_game *game)
{
	int i;

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
// GLOBALS NEEDED BY GLFW


extern char *g_f_bullet[];
extern char *g_coisas[];
extern char *g_yayaya[];
extern char *g_cenas[];
extern char *g_dementor[];
extern char *g_margarida[];
extern char *g_door[];
extern char *g_gun[];

int		game_load_textures(t_game *game)
{
	int i;

	ft_memset(game->tex, 0, sizeof(*game->tex) * NUM_TEX);
	game->tex[NO_TEX] = xpm_to_tex(g_north, TEX_TRANSPOSED);
	game->tex[SO_TEX] = xpm_to_tex(g_south, TEX_TRANSPOSED);
	game->tex[WE_TEX] = xpm_to_tex(g_west, TEX_TRANSPOSED);
	game->tex[EA_TEX] = xpm_to_tex(g_east, TEX_TRANSPOSED);
	game->tex[F_TEX] = xpm_to_tex(g_margarida, TEX_REGULAR);
	game->tex[C_TEX] = xpm_to_tex(g_margarida, TEX_REGULAR);
	game->tex[MEDI_TEX] = xpm_to_tex(g_medikit, TEX_TRANSPOSED);
	game->tex[AMMO_TEX] = xpm_to_tex(g_dementor, TEX_TRANSPOSED);
	game->tex[ENEMY_TEX] = xpm_to_tex(g_mario, TEX_TRANSPOSED);
	game->tex[BULLET_TEX] = xpm_to_tex(g_f_bullet, TEX_TRANSPOSED);
	game->tex[GUN_TEX] = xpm_to_tex(g_gun, TEX_REGULAR);
	game->tex[DOOR_TEX] = xpm_to_tex(g_door, TEX_TRANSPOSED);
	i = 0;
	while (i < NUM_TEX)
	{
		if (game->tex[i++] == NULL)
			return (0);
	}
	return (1);
}


int		game_start(t_game *game, char *game_config)
{
	*game = (t_game){};
	apply_all_settings(game);
	if (!map_parsing(&game->map, game_config) \
	|| !setup_sprites(game) \
	|| !game_load_textures(game))
		return (0);
	game_find_player_set_angles(game);
	player_setup(&game->player);
	if(!compass_setup(&game->compass))
		return (0);
	game->player.clock = &game->clock;
	game->hori_rays = malloc(sizeof(*game->hori_rays) * game->win.width);
	game->verti_rays = malloc(sizeof(*game->verti_rays) * game->win.height);
	game->player.vertical_correction = vertical_coefficient(game);
	if (!game->hori_rays || !game->verti_rays)
		return (perror_msg_int("malloc",0));
	setup_hitmap(game);
	game_setup_keys(game);
	if(!win_init_window(&game->win))
		return (0);
	return (1);
}

