/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:36:52 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:36:52 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (error_msg_int("cub3d: invalid number of arguments\n", \
			STDERR_FILENO, EXIT_FAILURE));
	if (!game_start(&game, av[1]))
	{
		game.exit_status = EXIT_FAILURE;
		free_game(&game);
	}
	rendering_loop(&game);
	free_game(&game);
	return (0);
}
