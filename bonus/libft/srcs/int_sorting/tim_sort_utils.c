/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tim_sort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:03:53 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 19:03:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_sorting.h"

int	helper_tern(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

/*
Using binary search to merge elements but unless there is some order before,
it is pretty useless and i wasted 5 hours dubugging this S. :)

static	tim_bin_srch(int *arr, int size, int target, int (*cmp)(int, int))
{
	int	high;
	int	low;
	int	mid;

	low = 0;
	high = size - 1;
	if (cmp(target, arr[high]))
		return (size);
	while (high - low > 1)
	{
		mid = (high + low) / 2;
		if (arr[mid] == target)
			return (mid);
		if (cmp(arr[mid], target))
			high = mid - 1;
		else
			low = mid + 1;
	}

	return (low + cmp(target, arr[low]));
}



static void	intersect(int *arr, int *copy, int *lmr, int (*cmp)(int, int))
{
	int len1;
	int len2;
	int i;
	int j;
	int k;
	int srch;

	len1 = lmr[1] - lmr[0] + 1;
	len2 = lmr[2] - lmr[1];
	ft_memcpy(copy, &arr[lmr[0]], (len1 + len2) * sizeof(*copy));
	i = 0;
	j = len1;
	k = lmr[0];

	while (i < len1 && j < (len1 + len2))
	{
		if (cmp(copy[i], copy[j]))
		{
			srch = tim_bin_srch(&copy[j], len1 + len2 - j, copy[i], cmp);
			ft_memcpy(&arr[k], &copy[j], sizeof(*arr) * srch);
			k += srch;
			j += srch;
			//printf("search: %d\n", srch);
		}
		else
		{
			srch = tim_bin_srch(&copy[i], len1 - i, copy[j], cmp);
			ft_memcpy(&arr[k], &copy[i], sizeof(*arr) * srch);
			k += srch;
			i += srch;
			//printf("search: %d\n", srch);
		}
	}
	if (i < len1)
		ft_memcpy(&arr[k], &copy[i], sizeof(*arr) * (len1 - i));
	if (j < (len1 + len2))
		ft_memcpy(&arr[k], &copy[j], sizeof(*arr) * (len1 + len2 - j));
}


*/
