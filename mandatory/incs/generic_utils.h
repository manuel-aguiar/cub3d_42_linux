/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:57:15 by cjoao-me          #+#    #+#             */
/*   Updated: 2024/03/08 14:57:15 by cjoao-me         ###   ########.fr       */
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

//ft_fabs.c
float	ft_fabs(float number);

//cubed_string_funcs.c
int		char_in_charset(char c, char *charset);
int		is_only_spaces(char *str);
int		count_char(char *str, char c);

//ft_ternary.c
float	float_ternary(bool cond, float yes, float no);
void	*ptr_ternary(bool cond, void *yes, void *no);

void	int_swap(int *first, int *second);
void	float_swap(float *first, float *second);

//float_equal.c
bool	float_equal(float num, float target, float error);

#endif
