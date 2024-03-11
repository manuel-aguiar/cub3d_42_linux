/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:05:49 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 12:05:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H

# define FT_MATH_H

int		bin_srch(int *arr, int size, int target, int (*cmp)(int, int));
int		ft_abs(int num);
int		ft_min(int first, int second);
int		ft_max(int first, int second);
float	ft_fmin(float first, float second);
float	ft_fmax(float first, float second);
int		ft_ternary(int cond, int ret_true, int ret_false);

#endif
