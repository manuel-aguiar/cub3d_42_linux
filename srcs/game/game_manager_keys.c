/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_key_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:43:50 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 12:43:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	game_key_manager(t_game *game)
{
	int keys;
	int move;
	int	new_height_state;

	keys = game->win.keys;

	if ((keys >> BIT_ESC) & 1)
		free_game(game);

	move = (((keys >> BIT_FRONT) & 1) << 3) | (((keys >> BIT_BACK) & 1) << 2) | (((keys >> BIT_LEFT) & 1) << 1) | (((keys >> BIT_RIGHT) & 1));
	move_player(game, move);


	new_height_state = -1;
	if (game->player.hgt_state == HGT_PRONE)
	{
		if ((keys >> BIT_CROUCH) & 1)
			new_height_state = HGT_CROUCH;
		else if (((keys >> BIT_PRONE) & 1) || ((keys >> BIT_JUMP) & 1))
			new_height_state = HGT_NORMAL;
		if (((keys >> BIT_JUMP) & 1))
			game->win.keys &= ~(1 << BIT_JUMP);
	}
	else if (game->player.hgt_state == HGT_CROUCH)
	{
		if ((keys >> BIT_PRONE) & 1)
			new_height_state = HGT_PRONE;
		else if (((keys >> BIT_CROUCH) & 1) || ((keys >> BIT_JUMP) & 1))
			new_height_state = HGT_NORMAL;
		if (((keys >> BIT_JUMP) & 1))
			game->win.keys &= ~(1 << BIT_JUMP);
	}
	else if (game->player.hgt_state == HGT_NORMAL)
	{
		if ((keys >> BIT_PRONE) & 1)
			new_height_state = HGT_PRONE;
		else if (((keys >> BIT_CROUCH) & 1))
			new_height_state = HGT_CROUCH;
		else if (((keys >> BIT_JUMP) & 1))
		{
			game->player.cur_jump_sense = game->player.jump_init;
			new_height_state = HGT_JUMP;
		}
	}
	else if (game->player.hgt_state == HGT_JUMP)
	{
		if (((keys >> BIT_JUMP) & 1))
		{
			game->player.cur_jump_sense += game->player.jump_inc;
			if(game->player.cur_jump_sense > game->player.jump_press_cap)
				game->player.cur_jump_sense = game->player.jump_press_cap;
		}
		else
		{
			if(game->player.cur_jump_sense > game->player.jump_release_cap)
				game->player.cur_jump_sense = game->player.jump_release_cap;
		}
	}
	if (new_height_state != -1)
		game->player.hgt_state = new_height_state;

	game->win.keys &= ~(1 << BIT_CROUCH);
	game->win.keys &= ~(1 << BIT_PRONE);
	game->player.is_sprinting = ((keys >> BIT_SPRINT) & 1) && !game->player.is_aiming && (((keys >> BIT_FRONT) & 1) << 3);

}
