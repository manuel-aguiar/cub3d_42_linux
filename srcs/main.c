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

void    endianess_test(void)
{
    char    arr[10];
    char    *ptr;
    
    ptr = arr;
    *(int *)ptr = 1;
    if (ptr[0] == 1)
        printf("little endian\n");
    else
        printf("big endian\n");
    
}

int main(int ac, char **av)
{
	t_game	game;	

	if (ac != 2)
		return (0 & ft_printf_fd(STDERR_FILENO, "cub3d: invalid number of arguments\n"));
	if (!game_start(&game, av[1]))
		return (0);
	win_render(&game, &game.win, win_key_callback);
	free_game(&game);
	return (0);
}


