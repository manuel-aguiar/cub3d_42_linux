/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:03:55 by manuel            #+#    #+#             */
/*   Updated: 2024/03/07 17:08:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ---- print_pxX.c ---- */
int	putcountaddr(void *address, int fd);
int	putcounthex(unsigned int nb, char *base, int fd);

/* ---- print_csdiu_perc.c ---- */
int	putcountint(int nb, int fd);
int	putcountunint(unsigned int nb, int fd);
int	putcountstr(char *str, int fd);
int	putcountchar(char c, int fd);

static int	flagcheck(char c, char *flags, va_list ptr)
{
	if (!flags)
		return (0);
	while (*flags)
	{
		if (c == *flags)
			return (1);
		flags++;
	}
	va_arg(ptr, int);
	return (0);
}

static int	printformat(va_list ptr, char flag, int fd)
{
	if (!flagcheck(flag, FLAGS, ptr))
		return (0);
	if (flag == 'c')
		return (putcountchar(va_arg(ptr, int), fd));
	if (flag == 's')
		return (putcountstr(va_arg(ptr, char *), fd));
	if (flag == 'p')
		return (putcountaddr(va_arg(ptr, void *), fd));
	if (flag == 'd' || flag == 'i')
		return (putcountint(va_arg(ptr, int), fd));
	if (flag == 'u')
		return (putcountunint(va_arg(ptr, unsigned int), fd));
	if (flag == 'x')
		return (putcounthex(va_arg(ptr, unsigned int), HEXS, fd));
	if (flag == 'X')
		return (putcounthex(va_arg(ptr, unsigned int), HEXB, fd));
	if (flag == '%')
		return (putcountchar('%', fd));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	int		i;

	i = 0;
	va_start(ptr, str);
	while (*str)
	{
		if (*str != '%')
		{
			i += write(1, str, 1);
		}
		else
		{
			i += printformat(ptr, *(str + 1), 1);
			str++;
		}
		str++;
	}
	va_end(ptr);
	return (i);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	ptr;
	int		i;

	i = 0;
	va_start(ptr, str);
	while (*str)
	{
		if (*str != '%')
			i += write(fd, str, 1);
		else
		{
			i += printformat(ptr, *(str + 1), fd);
			str++;
		}
		str++;
	}
	va_end(ptr);
	return (i);
}
