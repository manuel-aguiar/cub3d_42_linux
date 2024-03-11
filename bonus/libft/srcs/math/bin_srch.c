/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_srch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:11:16 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 19:11:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	bin_srch(int *arr, int size, int target, int (*cmp)(int, int))
{
	int	high;
	int	low;
	int	mid;

	low = 0;
	high = size - 1;
	if (arr[low] == target)
		return (low);
	if (arr[high] == target)
		return (high);
	while (high - low > 1)
	{
		if (arr[low] == target)
			return (low);
		if (arr[high] == target)
			return (high);
		mid = low + (high - low) / 2;
		if (arr[mid] == target)
			return (mid);
		if (cmp(arr[mid], target))
			high = mid;
		else
			low = mid;
	}
	return (-1);
}
