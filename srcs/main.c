/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:43:31 by marvin            #+#    #+#             */
/*   Updated: 2024/01/11 14:43:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (error_msg_int("cub3d: invalid number of arguments\n", \
			STDERR_FILENO, 0));
	if (!game_start(&game, av[1]))
	{
		game.exit_status = EXIT_FAILURE;
		free_game(&game);
	}
	rendering_loop(&game);
	free_game(&game);
	return (0);
}
