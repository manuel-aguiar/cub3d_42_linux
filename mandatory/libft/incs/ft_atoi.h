/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:26:05 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 16:26:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ATOI_H

# define FT_ATOI_H

# include <stdlib.h>
# include <ft_string.h>

# include "error_handling.h"
/*
	DESCRIPTION OF FUNCTIONS

ft_atoi: replica of libc atoi;
ft_atoi_overflow: same as ft_atoi but stops in case of overflow
ft_atoiable: same as atoi overflow, return value is 1
	on success and zero on failure;
ft_atoi_arr: takes a matrix of char arrays and performs atoi on each one,
	creating an array of integers. In case of overflow, or malloc failure
	returns 0 and sets arr pointer to NULL. returns 1 on success.
ft_itoa: reverse atoi, converts number to char array

*/

int		ft_atoi(const char *nptr);
int		ft_atoi_overf(char *str);
int		ft_atoiable(char *str, int *placenum);
int		ft_atoi_arr(int **dest, int ac, char **av);
char	*ft_itoa(int nb);
int		ft_atoi_base(char *str, char *base);

#endif
