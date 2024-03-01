/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:03:55 by manuel            #+#    #+#             */
/*   Updated: 2023/08/17 19:44:11 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# define HEXS "0123456789abcdef"
# define HEXB "0123456789ABCDEF"
# define HEXLEN 16
# define FLAGS "cspdiuxX%"
# include <stdarg.h>

# include <unistd.h>    /* DELETE */
# include "ft_string.h"

/* ---- ft_printf.c ---- */
int	ft_printf(const char *str, ...);
int	ft_printf_fd(int fd, const char *str, ...);

#endif
