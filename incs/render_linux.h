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
	double 		cur_x;
	double 		cur_y;
	double		prev_x;
	double		prev_y;
	int			buttons;
};


// all keys a buttons are according to glfw, change to mlx

enum e_keys_vals
{
	KEY_ESC = GLFW_KEY_ESCAPE,
	KEY_FRONT = GLFW_KEY_W,
	KEY_BACK = GLFW_KEY_S,
	KEY_LEFT = GLFW_KEY_A,
	KEY_RIGHT = GLFW_KEY_D,
	KEY_JUMP = GLFW_KEY_SPACE,
	KEY_SPRINT = GLFW_KEY_LEFT_SHIFT,
	KEY_CROUCH = GLFW_KEY_X,
	KEY_PRONE = GLFW_KEY_Z,
	KEY_BLUR_T = GLFW_KEY_1,
	KEY_FLOOR_REFL_T = GLFW_KEY_2,
	KEY_CEIL_REFL_T = GLFW_KEY_3,
	KEY_SHADE_T = GLFW_KEY_4,
	KEY_HUD_T = GLFW_KEY_5,
	KEY_PAUSE_T = GLFW_KEY_P,
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
	BUT_AIM = GLFW_MOUSE_BUTTON_RIGHT,
	BUT_SHOOT = GLFW_MOUSE_BUTTON_LEFT,
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
    struct timeb  	start;
    struct timeb  	end;
    size_t			elapsed;
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
	void			*window;
	t_mlx_img		*front_buf;
	int				width;
	int				height;
	int				rgb_size;
	char			name[6];
	t_pause_blur	blur;
	void			(*set_pixel)(t_win *win, int x, int y, int color);
	int				(*get_pixel)(t_win *win, int x, int y);
};



//win_init_window.c
int			win_init_window(t_win *win);
int			free_win_glfw(t_win *win);

//win_keys.c
void	win_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void 	win_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void	win_mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//win_render_loop.c


//win_pixels.c
void	win_set_pixel(t_win *win, int x, int y, int color);
int		win_get_pixel(t_win *win, int x, int y);
int		avg_colour(int start, int end, int num, int den);
void	swap_pixels(t_pixel *start, t_pixel *end);



void chatgpt_anticircle(t_win *win, t_pixel centre, int radius, int color);


void	window_pause_manager(t_win *win, e_pause_state state, bool blur_on);

void	start_clock(t_clock *clock);
void	update_clock(t_clock *clock);

#endif