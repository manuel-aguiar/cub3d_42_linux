/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:49:02 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 17:49:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H

# define FT_STRING_H

# include <stdlib.h>

# include "ft_memfunc.h"
# include "error_handling.h"

typedef unsigned long	t_ulong;
typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;
typedef const char		t_cchar;

/* individual character functions*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
/* best function programmers ever created*/
size_t	ft_strlen(t_cchar *str);

/* functions i hope i never have to use ever again*/
size_t	ft_strlcpy(char *dst, t_cchar *src, size_t size);
size_t	ft_strlcat(char *dst, t_cchar *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(t_cchar *s, int c);
char	*ft_strrchr(t_cchar *s, int c);
int		ft_strncmp(t_cchar *s1, t_cchar *s2, size_t n);
char	*ft_strdup(t_cchar *s);
char	*ft_strnstr(t_cchar *big, t_cchar *little, size_t len);
char	*ft_strmapi(char *s, char (*f)(t_uint, char));
void	ft_striteri(char *s, void (*f)(t_uint, char *));
char	*ft_substr(t_cchar *s, t_uint start, size_t len);
char	*ft_strjoin(t_cchar *s1, t_cchar *s2);
char	*ft_strtrim(t_cchar *s1, t_cchar *set);

/* the most evil and useful function ever invented*/
char	**ft_split(t_cchar *s, char c);
char	**ft_split_count(t_cchar *s, char *sepset, int *place_count);
void	ft_free_split(void *table);

#endif
