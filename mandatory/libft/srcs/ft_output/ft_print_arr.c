/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:08:02 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 10:08:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_output.h"

void	ft_print_arr(int *arr, int size, void (*pnt)(int))
{
	int	i;

	if (!arr || !size || !pnt)
		return ;
	i = 0;
	while (i < size)
	{
		pnt(arr[i]);
		i++;
	}
	ft_printf("\n");
}
