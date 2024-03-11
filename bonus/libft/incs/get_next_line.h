/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:30:35 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/01/12 12:00:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# include "ft_memfunc.h"
# include "error_handling.h"

typedef struct s_gnl_len
{
	char	*line;
	int		len;
	t_uchar	status;
}	t_gnl_len;

enum	e_gnl
{
	GNL_OK,
	GNL_FAILURE,
	GNL_BAD_FD,
	GNL_EOF,
};

/* get_next_line.c*/
char		*get_next_line(int fd);
char		*get_next_line_multi(int fd);
t_gnl_len	*get_next_line_len(int fd);
void		free_gnl_len(void *gnl);
#endif
