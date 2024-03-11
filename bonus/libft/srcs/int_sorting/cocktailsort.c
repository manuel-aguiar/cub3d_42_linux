/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cocktailsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:14:14 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 19:14:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_sorting.h"

static void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	frontrun(int *arr, int len, int swapn, int (*cmp)(int, int))
{
	int	i;
	int	keep_sorting;

	keep_sorting = 0;
	i = swapn;
	while (i < (len - swapn - 1))
	{
		if (cmp(arr[i], arr[i + 1]))
			swap(&arr[i], &arr[i + 1]);
		if (i > 0 && !keep_sorting)
			if (cmp(arr[i - 1], arr[i]))
				keep_sorting = 1;
		i++;
	}
	return (keep_sorting);
}

static int	backrun(int *arr, int len, int swapn, int (*cmp)(int, int))
{
	int	j;
	int	keep_sorting;

	keep_sorting = 0;
	j = (len - swapn - 1) - 2;
	while (j >= swapn)
	{
		if (cmp(arr[j], arr[j + 1]))
			swap(&arr[j], &arr[j + 1]);
		if (j > 0 && !keep_sorting)
			if (cmp(arr[j - 1], arr[j]))
				keep_sorting = 1;
		j--;
	}
	return (keep_sorting);
}

int	*cocktail_sort(int *arr, int len, int (*cmp)(int, int))
{
	int	swapn;
	int	sorttoright;
	int	sorttoleft;

	swapn = 0;
	sorttoright = 1;
	sorttoleft = 0;
	while (swapn < (len / 2) && sorttoright)
	{
		if (sorttoright)
			sorttoleft = frontrun(arr, len, swapn, cmp);
		sorttoright = 0;
		if (sorttoleft)
			sorttoright = backrun(arr, len, swapn, cmp);
		sorttoleft = 0;
		swapn++;
	}
	return (arr);
}
