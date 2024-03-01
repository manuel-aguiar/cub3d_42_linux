/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:11:21 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 12:11:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_INPUTS_H

# define USER_INPUTS_H

# include <GLFW/glfw3.h>

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




#endif