/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:52:33 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 12:52:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_settings.h"

void	settings_template_door(t_door *door)
{
	*door = (t_door){};
	door->move_sense = DOOR_MOVE_SENSE;
	door->dist_sense = fpow_2(DOOR_DIST_SENSE);
	door->base_z = DOOR_Z;
	door->height = DOOR_HGT;
	door->state = DOOR_CLOSED;
}

void	settings_template_ammo(t_ammo *ammo)
{
	*ammo = (t_ammo){};
	ammo->ammopoints = AMMO_RESOURCE;
	ammo->unit_size = AMMO_UNIT;
	ammo->height = AMMO_HGT;
	ammo->float_radius = AMMO_FLOAT_RADIUS;
	ammo->width = AMMO_WDT;
	ammo->base_z = AMMO_Z;
	ammo->z_sense = AMMO_Z_SENSE;
}

void	settings_template_medi(t_medi *medi)
{
	*medi = (t_medi){};
	medi->lifepoints = MEDI_RESOURCE;
	medi->unit_size = MEDI_UNIT;
	medi->height = MEDI_HGT;
	medi->width = MEDI_WDT;
	medi->float_radius = MEDI_FLOAT_RADIUS;
	medi->base_z = MEDI_Z;
	medi->z_sense = MEDI_Z_SENSE;
}

void	settings_template_bullet(t_bullet *bullet)
{
	*bullet = (t_bullet){};
	bullet->unit_size = BULLET_UNIT_SIZE;
	bullet->move_sense = BULLET_MOVE_SENSE;
	bullet->height = BULLET_HGT;
	bullet->attack_val = BULLET_ATTACK_VAL;
	bullet->base_z = BULLET_BASE_Z;
}
