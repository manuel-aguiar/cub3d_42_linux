/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:20:08 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 16:20:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERIC_UTILS_H

# define GENERIC_UTILS_H

# include "libft.h"

# define P_MY_PI 3.14159265f


//clamp.c
int		int_clamp(int value, int min, int max);
float	float_clamp(float value, float min, float max);

//radian_truncate.c
float	radian_truncate(float radian);

//ft_split_count_replenish.c
char	**ft_split_count_replenish(t_cchar *s, t_cchar *og, \
		char *sepset, int *place_count);

//fpow_2.c
float	fpow_2(float number);

float	ft_fabs(float number);

int		char_in_charset(char c, char *charset);
int		is_only_spaces(char *str);

//ft_ternary.c
float	float_ternary(bool cond, float yes, float no);
void	*ptr_ternary(bool cond, void *yes, void *no);


void	int_swap(int *first, int *second);
void	float_swap(float *first, float *second);

#endif