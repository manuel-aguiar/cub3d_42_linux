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
# include <time.h> 
# include <sys/time.h> 

# define MY_PI 3.14159265f

# include "libft.h"
# include <stdbool.h>
# include "vector.h"
# include "pixel_point.h"

# define RGB_SIZE 4 

typedef struct s_win t_win;
typedef struct s_pixel t_pixel;


typedef struct s_mouse t_mouse;

// GLOBALS NEEDED BY GLFW

extern 	int 		g_keys;
extern  t_mouse		g_mouse;

struct s_mouse
{
	int	buttons;
	int	cur_x;
	int	cur_y;
	int	prev_x;
	int	prev_y;
};


// all keys a buttons are according to glfw, change to mlx

enum e_keys_vals
{
	KEY_ESC = 65307,
	KEY_FRONT = 'w',
	KEY_BACK = 's',
	KEY_LEFT = 'a',
	KEY_RIGHT = 'd',
	KEY_JUMP = ' ',
	KEY_SPRINT = 'l',	//change to shift later
	KEY_CROUCH = 'x',
	KEY_PRONE = 'z',
	KEY_BLUR_T = '1',
	KEY_FLOOR_REFL_T = '2',
	KEY_CEIL_REFL_T = '3',
	KEY_SHADE_T = '4',
	KEY_HUD_T = '5',
	KEY_PAUSE_T = 'p',
	KEY_COUNT = 19,
};

enum e_keys_bits
{
	BIT_ESC,
	BIT_FRONT,
	BIT_BACK,
	BIT_LEFT,
	BIT_RIGHT,
	BIT_JUMP,
	BIT_SPRINT,
	BIT_CROUCH,
	BIT_PRONE,
	BIT_BLUR_T,
	BIT_FLOOR_REFL_T,
	BIT_CEIL_REFL_T,
	BIT_SHADE_T,
	BIT_HUD_T,
	BIT_PAUSE_T,
};

enum e_button_vals
{
	BUT_AIM = 1,
	BUT_SHOOT = 2,
	BUT_COUNT = 2,
};

enum e_button_bits
{
	BIT_AIM = 1,
	BIT_SHOOT,
	BIT_COUNT,
};

typedef struct s_clock
{
    struct timeval  start;
    struct timeval  end;
    size_t          elapsed;
}   t_clock;

typedef struct s_pause_blur
{
	float		kernel[31];
	int			save_pixels[31];
	int			kernel_size;
	int			kernel_centre;
	int			max_kernel;
	int			cur_sigma;
	int			min_sigma;
	int			max_sigma;
	int			pause_time;
	t_clock		clock;
	long int	elapsed;
	char		*first;
	char		*second;
	char		*save_front;
	int			rgb_size;
	int			height;
	int			width;
}	t_pause_blur;

typedef enum
{
	PAUSE_OFF,
	PAUSE_ON,
}	e_pause_state;

typedef struct s_mlx_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx_img;

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
	t_pause_blur	blur;
	void			(*set_pixel)(t_win *win, int x, int y, int color);
	int				(*get_pixel)(t_win *win, int x, int y);
};



//win_init_window.c
int			win_init_window(t_win *win);
int			free_window(t_win *win);

//win_keys.c
int		mouse_position(int x, int y, t_win *win);
int		mouse_release(int button, int x, int y, t_win *win);
void    mouse_press(int button, int x, int y, t_win *win);
void	key_press(int keycode, t_win *win);
void	key_release(int keycode, t_win *win);
//win_render_loop.c


//win_pixels.c
void	linux_set_pixel(t_win *win, int x, int y, int color);
int		linux_get_pixel(t_win *win, int x, int y);
int		avg_colour(int start, int end, int num, int den);
void	swap_pixels(t_pixel *start, t_pixel *end);



void 	chatgpt_anticircle(t_win *win, t_pixel centre, int radius, int color);


void	window_pause_manager(t_win *win, e_pause_state state, bool blur_on);

void	start_clock(t_clock *clock);
void	update_clock(t_clock *clock);

#endif