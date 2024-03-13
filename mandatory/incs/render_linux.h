/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_linux.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:10:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 10:10:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_LINUX_H

# define RENDER_LINUX_H

# include <mlx.h>

# define MY_PI 3.14159265f

# include "libft.h"
# include <stdbool.h>
# include "vector.h"
# include "pixel_point.h"

# define RGB_SIZE 4

typedef struct s_win	t_win;
typedef struct s_pixel	t_pixel;
typedef struct s_mouse	t_mouse;

struct s_mouse
{
	int	buttons;
	int	cur_x;
	int	cur_y;
	int	prev_x;
	int	prev_y;
};

enum e_keys_vals
{
	KEY_ESC = 65307,
	KEY_FRONT = 'w',
	KEY_BACK = 's',
	KEY_LEFT = 'a',
	KEY_RIGHT = 'd',
	KEY_ROT_L = 65361,
	KEY_ROT_R = 65363,
};

enum e_keys_bits
{
	BIT_ESC,
	BIT_FRONT,
	BIT_BACK,
	BIT_LEFT,
	BIT_RIGHT,
	BIT_ROT_L,
	BIT_ROT_R,
};

enum e_button_vals
{
	BUT_AIM = 3,
	BUT_SHOOT = 1,
	BUT_COUNT = 2,
};

enum e_button_bits
{
	BIT_SHOOT = 1,
	BIT_AIM = 2,
	BIT_COUNT = 2,
};

typedef enum e_pause_state
{
	PAUSE_OFF,
	PAUSE_ON,
}	t_pause_state;

typedef struct s_mlx_img
{
	void	*img;
	char	*pixels;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_mlx_img;

typedef struct s_xpm_to_win
{
	t_mlx_img	*tex;
	int			win_low_x;
	int			win_low_y;
	int			pix_width;
	int			pix_height;
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	int			this_color;
}	t_xpm_to_win;

struct s_win
{
	void			*mlx;
	void			*mlx_win;
	t_mlx_img		front_buf;
	int				width;
	int				height;
	int				rgb_size;
	char			name[6];
	t_mouse			mouse;
	int				keys;
	void			(*set_pixel)(t_win *win, int x, int y, int color);
	int				(*get_pixel)(t_win *win, int x, int y);
};

//win_init_window.c
int		win_init_window(t_win *win);
int		free_window(t_win *win);

//key and mouse callbacks
int		mouse_position(int x, int y, t_win *win);
int		mouse_release(int button, int x, int y, t_win *win);
int		mouse_press(int button, int x, int y, t_win *win);
int		key_press(int keycode, t_win *win);
int		key_release(int keycode, t_win *win);

//win_pixels.c
void	linux_set_pixel(t_win *win, int x, int y, int color);
int		linux_get_pixel(t_win *win, int x, int y);
int		avg_colour(int start, int end, int num, int den);
void	swap_pixels(t_pixel *start, t_pixel *end);

void	xpm_to_window(t_win *win, t_xpm_to_win	*xpm);

#endif
