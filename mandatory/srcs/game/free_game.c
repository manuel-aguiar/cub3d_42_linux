/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:01:40 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 12:01:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < NUM_TEX)
	{
		if (game->tex[i].img)
			mlx_destroy_image(game->win.mlx, game->tex[i].img);
		i++;
	}
}

int	free_game(t_game *game)
{
	destroy_textures(game);
	free_window(&game->win);
	free_map(&game->map);
	destroy_parsing(&game->parsing);
	if (game->hori_rays)
		free(game->hori_rays);
	if (game->verti_rays)
		free(game->verti_rays);
	exit(game->exit_status);
	return (1);
}
