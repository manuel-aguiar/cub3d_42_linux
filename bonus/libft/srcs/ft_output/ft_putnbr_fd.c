/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:33:58 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:33:58 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_output.h"

int	ft_putnbr_fd(int nb, int fd)
{
	char	str[11];
	char	print;
	int		i;
	char	sign;

	sign = 1;
	i = sizeof(str);
	if (nb < 0)
		sign = -1;
	if (nb == 0)
		str[--i] = '0';
	while (nb != 0)
	{
		print = nb % 10;
		if (print < 0)
			print *= -1;
		str[--i] = print + '0';
		nb /= 10;
	}
	if (sign == -1)
		str[--i] = '-';
	return (write(fd, &str[i], sizeof(str) - i));
}

int	ft_putnbr(int nb)
{
	return (ft_putnbr_fd(nb, 1));
}

/*
#include <time.h>
#include <stdio.h>
void printit(int nbr, int fd)
{
	if (nbr > 10 || nbr < -10)
		printit(nbr / 10, fd);
	nbr %= 10;
	if (nbr < 0)
		nbr *= -1;
	nbr += '0';
	write(fd, &nbr, 1);
}

void new_putnbr(int nbr, int fd)
{
	if (nbr < 0)
		write(fd, "-", 1);
	printit(nbr, fd);
}


int main()
{

	int times = 1000;


	clock_t t;
	t = clock();
	int i = 0;
	while (i < times)
	{
		ft_putnbr_fd(i, 1);
		i++;
	}
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;


	clock_t x;
	x = clock();
	int a = 0;
	while (a < times)
	{
		printf("%d", a);
		a++;
	}
	x = clock() - x;
	double time_takenn = ((double)x)/CLOCKS_PER_SEC;



	clock_t z;
	z = clock();
	int l = 0;
	while (l < times)
	{
		new_putnbr(l, 1);
		l++;
	}
	z = clock() - z;
	double time_takennnn = ((double)z)/CLOCKS_PER_SEC;

	printf("\nmy putnbr   %f\n", time_taken);
	printf("printf took %f\n", time_takenn);
	printf("usual took  %f\n", time_takennnn);


}
*/
