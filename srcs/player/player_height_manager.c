/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_height_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:14:16 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 13:42:45 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	manage_prone_height(t_player *player, int *keys, int *new_height_state)
{
	(void)player;
	if ((*keys >> BIT_CROUCH) & 1)
		*new_height_state = HGT_CROUCH;
	else if (((*keys >> BIT_PRONE) & 1) || ((*keys >> BIT_JUMP) & 1))
		*new_height_state = HGT_NORMAL;
	if (((*keys >> BIT_JUMP) & 1))
		*keys &= ~(1 << BIT_JUMP);
}

void	manage_crouch_height(t_player *player, int *keys, int *new_height_state)
{
	(void)player;
	if ((*keys >> BIT_PRONE) & 1)
		*new_height_state = HGT_PRONE;
	else if (((*keys >> BIT_CROUCH) & 1) || ((*keys >> BIT_JUMP) & 1))
		*new_height_state = HGT_NORMAL;
	if (((*keys >> BIT_JUMP) & 1))
		*keys &= ~(1 << BIT_JUMP);
}

void	manage_normal_height(t_player *player, int *keys, int *new_height_state)
{
	if ((*keys >> BIT_PRONE) & 1)
		*new_height_state = HGT_PRONE;
	else if (((*keys >> BIT_CROUCH) & 1))
		*new_height_state = HGT_CROUCH;
	else if (((*keys >> BIT_JUMP) & 1))
	{
		player->cur_jump_sense = player->jump_init;
		*new_height_state = HGT_JUMP;
	}
}

void	manage_jump_height(t_player *player, int *keys, int *new_height_state)
{
	(void)new_height_state;
	if (((*keys >> BIT_JUMP) & 1))
	{
		player->cur_jump_sense += player->jump_inc;
		if (player->cur_jump_sense > player->jump_press_cap)
			player->cur_jump_sense = player->jump_press_cap;
	}
	else
	{
		if (player->cur_jump_sense > player->jump_release_cap)
			player->cur_jump_sense = player->jump_release_cap;
	}
}
