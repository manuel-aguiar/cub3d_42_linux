/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:29:55 by marvin            #+#    #+#             */
/*   Updated: 2024/02/16 11:29:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

void	first_pass(t_win *win, t_compass *comp, t_comp_blur	*blur);
void	second_pass(t_compass *comp, t_comp_blur *blur);

void	transpose_square_matrix(int *mat, int size)
{
	int	i;
	int	j;
	int	index1;
	int	index2;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			index1 = i * size + j;
			index2 = j * size + i;
			int_swap(&mat[index1], &mat[index2]);
			j++;
		}
		i++;
	}
}

void	blur_compass(t_win *win, t_compass *comp)
{
	int			height;
	t_comp_blur	*blur;

	blur = &comp->blur;
	height = blur->blur_height;
	first_pass(win, comp, blur);
	transpose_square_matrix(blur->hori_blur, height);
	second_pass(comp, blur);
	transpose_square_matrix(blur->verti_blur, height);
}
