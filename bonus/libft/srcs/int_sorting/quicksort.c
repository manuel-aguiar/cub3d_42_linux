/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:12:11 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 19:12:11 by marvin           ###   ########.fr       */
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

static int	partition(int arr[], int low, int high, int (*cmp)(int, int))
{
	int	pivot;
	int	i;
	int	j;

	pivot = arr[low];
	i = low - 1;
	j = high + 1;
	while (1)
	{
		i++;
		while (cmp(pivot, arr[i]))
			i++;
		j--;
		while (cmp(arr[j], pivot))
			j--;
		if (i >= j)
			return (j);
		swap(&arr[i], &arr[j]);
	}
}

static void	qs_recursion(int *arr, int low, int high, int (*cmp)(int, int))
{
	int	part;

	if (low < high)
	{
		part = partition(arr, low, high, cmp);
		qs_recursion(arr, low, part, cmp);
		qs_recursion(arr, part + 1, high, cmp);
	}
}

int	*quicksort(int *arr, int size, int (*cmp)(int, int))
{
	qs_recursion(arr, 0, size - 1, cmp);
	return (arr);
}
