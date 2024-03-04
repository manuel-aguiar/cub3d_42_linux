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

int	free_game(t_game *game)
{
	int i;

	free_window(&game->win);
	free_compass(&game->compass);
	free_map(&game->map);
	if (game->hori_rays)
		free(game->hori_rays);
	if (game->verti_rays)
		free(game->verti_rays);
	i = 0;
	while (i < NUM_TEX)
	{
		if (game->tex[i])
			xpm_tex_free(game->tex[i]);
		i++;
	}
	if (game->sprites)
	{
		i = 0;
		while (i < game->sprite_count)
		{
			if (game->sprites[i].data)
				free(game->sprites[i].data);
			i++;
		}
		free(game->sprites);
	}
	if (game->sorted)
		free(game->sorted);
	exit(EXIT_SUCCESS);
	return (1);
}