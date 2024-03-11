/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:13:09 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 19:13:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_sorting.h"

/*
totally not norminette compliant....... YET
unprotected mallocs.... FOR NOW


static void ms_merge(int *arr, int left, int mid, int right, \
		int (*cmp)(int, int))
{
	int i;
	int j;
	int k;

	int lenleft;
	int lenright;

	int *larr;
	int *rarr;

	lenleft = mid - left + 1;
	lenright = right - mid;

	larr = malloc(sizeof *larr * lenleft);     //unprotected
	rarr = malloc(sizeof *rarr * lenright);    //unprotected

	i = 0;

	while(i < lenleft)
	{
		larr[i] = arr[left + i];
		i++;
	}

	j = 0;
	while(j < lenright)
	{
		rarr[j] = arr[mid + 1 + j];
		j++;
	}

	i = 0;
	j = 0;
	k = left;

	while(i < lenleft && j < lenright)
	{
		if (cmp(rarr[j], larr[i]))
		{
			arr[k] = larr[i];
			i++;
		}
		else
		{
			arr[k] = rarr[j];
			j++;
		}
		k++;
	}

	while(i < lenleft)
	{
		arr[k] = larr[i];
		i++;
		k++;
	}

	free(larr);

	while(j < lenright)
	{
		arr[k] = rarr[j];
		j++;
		k++;
	}

	free(rarr);


}

static void ms_split(int *arr, int left, int right, int (*cmp)(int, int))
{
	int mid;

	if (right > left)
	{

			mid = left + (right - left) / 2;
			ms_split(arr,left,mid,cmp);
			ms_split(arr, mid + 1, right,cmp);
			ms_merge(arr,left,mid,right,cmp);

	}
}

int *mergesort(int *arr, int len, int (*cmp)(int, int))
{
	ms_split(arr,0, len - 1, cmp);
	return (arr);
}
*/
