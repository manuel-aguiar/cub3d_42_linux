/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:29:38 by marvin            #+#    #+#             */
/*   Updated: 2024/02/05 11:29:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_PARSER_H

# define XPM_PARSER_H

# include "pixel_point.h"
# include "libft.h"

typedef enum
{
	TEX_REGULAR,
	TEX_TRANSPOSED
}	e_tex_type;

typedef struct s_xpm_pair
{
	char	*id;
	int		color;
}	t_xpm_pair;

typedef struct s_xpm_tex
{
	int			width;
	int			height;
	char		*pixels;
	e_tex_type	type;
}	t_xpm_tex;

typedef struct s_xpm_parser
{
	char 		**xpm;
	t_xpm_tex	*tex;
	t_xpm_pair	*id_color;
	char		**split;
	int			s_count;
	int			color_count;
	int			id_len;
	e_tex_type	type;
}	t_xpm_parser;

t_xpm_tex	*xpm_to_tex(char *xpm[], e_tex_type tex_type);
int			xpm_tex_copy_transpose(t_xpm_tex *tex);
void		xpm_tex_free(t_xpm_tex *tex);

#endif
