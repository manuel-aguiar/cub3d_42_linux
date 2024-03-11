/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:03:45 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 19:03:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_SORTING_H

# define INT_SORTING_H

# include "ft_memfunc.h"
# include "error_handling.h"
# include <stdlib.h>

# define TIM_SORT_RUN 32

void	*quicksort_pointers(void *arr, int size, int (*cmp)(void *, void *));
int		*mergesort(int *arr, int len, int (*cmp)(int, int));
int		*quicksort(int *arr, int size, int (*cmp)(int, int));
int		tim_sort(int *arr, int n, int (*cmp)(int, int));
int		*cocktail_sort(int *arr, int len, int (*cmp)(int, int));
//int *insertion_sort(int arr[], int left, int (*cmp)(int, int));
//int *mysort(int *arr, int len, int (*cmp)(int, int));
//int bin_srch(int *arr, int size, int target, int (*cmp)(int, int));

#endif
