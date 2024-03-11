/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charmat_quicksort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:25:30 by marvin            #+#    #+#             */
/*   Updated: 2023/08/23 12:25:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_sorting.h"

static void	swap(void *a, void *b)
{
	t_uchar	*temp;
	t_uchar	**a_new;
	t_uchar	**b_new;

	a_new = (t_uchar **)a;
	b_new = (t_uchar **)b;
	temp = *a_new;
	*a_new = *b_new;
	*b_new = temp;
}

static int	partition(void *arr, int low, int high, int (*cmp)(void *, void *))
{
	t_uchar	**myarr;
	t_uchar	*pivot;
	int		i;
	int		j;

	myarr = (t_uchar **)arr;
	pivot = myarr[low];
	i = low - 1;
	j = high + 1;
	while (1)
	{
		i++;
		while (cmp(pivot, myarr[i]))
			i++;
		j--;
		while (cmp(myarr[j], pivot))
			j--;
		if (i >= j)
			return (j);
		swap(&myarr[i], &myarr[j]);
	}
}

static void	qs_recursion(void *arr, int low, int high, \
						int (*cmp)(void *, void *))
{
	int			part;
	t_uchar		**myarr;

	myarr = (t_uchar **)arr;
	if (low < high)
	{
		part = partition(myarr, low, high, cmp);
		qs_recursion(myarr, low, part, cmp);
		qs_recursion(myarr, part + 1, high, cmp);
	}
}

void	*quicksort_pointers(void *arr, int size, int (*cmp)(void *, void *))
{
	qs_recursion(arr, 0, size - 1, cmp);
	return (arr);
}
