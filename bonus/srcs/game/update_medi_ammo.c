/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_medi_ammo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:10:47 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 15:10:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	update_ammokit(t_game *game, t_sprite *sprite)
{
	t_ammo	*ammo;

	ammo = (t_ammo *)sprite->data;
	sprite->cur_z = ammo->base_z - game->float_sin * ammo->float_radius;
	if (sprite->dist <= game->player.unit_size \
	&& game->player.ammo[CTR_CUR] < game->player.ammo[CTR_MAX])
	{
		game->player.ammo[CTR_CUR] = ft_min(game->player.ammo[CTR_CUR] \
		+ ammo->ammopoints, game->player.ammo[CTR_MAX]);
		sprite->status = GONE;
	}
}

void	update_medikit(t_game *game, t_sprite *sprite)
{
	t_medi	*medi;

	medi = (t_medi *)sprite->data;
	sprite->cur_z = medi->base_z - game->float_sin * medi->float_radius;
	if (sprite->dist <= game->player.unit_size \
	&& game->player.health[CTR_CUR] < game->player.health[CTR_MAX])
	{
		game->player.health[CTR_CUR] = ft_min(game->player.health[CTR_CUR] \
		+ medi->lifepoints, game->player.health[CTR_MAX]);
		sprite->status = GONE;
	}
}
