/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_pause_blur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:33:24 by marvin            #+#    #+#             */
/*   Updated: 2024/02/19 12:33:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "render_linux.h"

void	window_transpose(char *dest, char *src, int width, \
	int height, int rgb_size)
{
	int	row;
	int	col;
	int src_index;
	int	dest_index;

	row = 0;
	while (row < height)
	{
		col = 0;
		while(col < width)
		{
			src_index = (col + row * width) * rgb_size;
			dest_index = (row + col * height) * rgb_size;
			*(int *)(&dest[dest_index]) = *(int *)(&src[src_index]);
			col++;
		}
		row++;
	}
}

void	dump_blur_to_front_buf(t_win *win, t_pause_blur *blur, char *dump)
{
	int y;
	int index;
	int size;

	y = blur->kernel_centre;
	while (y < win->height - blur->kernel_centre)
	{
		index = (blur->kernel_centre + y * win->width) * win->rgb_size;
		size = (win->width - (int)(blur->kernel_size / 2) * 2) * win->rgb_size;
		ft_memcpy(&win->front_buf[index], &dump[index], size);
		y++;
	}
}

static inline void	fill_kernel_colors(t_pause_blur *blur, float colors[4], int index)
{
	colors[0] += ((blur->save_pixels[index] >> 24) & 0xff) * blur->kernel[index];
	colors[1] += ((blur->save_pixels[index] >> 16) & 0xff) * blur->kernel[index];
	colors[2] += ((blur->save_pixels[index] >> 8) & 0xff) * blur->kernel[index];
	colors[3] += ((blur->save_pixels[index] >> 0) & 0xff) * blur->kernel[index];
}

void	blur_horizontal(t_pause_blur *blur, char *dest, char *src, int width, int height)
{
	int		blur_index;
	int		y;
	int		x;
	float	colors[4];
	int 	i;
	
	y = blur->kernel_size / 2;
	while (y < height - blur->kernel_size / 2)
	{
		x = blur->kernel_size / 2;
		while (x < width - blur->kernel_size / 2)
		{
			blur_index = (y * width + x) * blur->rgb_size;
			ft_memset(colors, 0, sizeof(colors));
			i = 0;					
			while (i < blur->kernel_size)
			{
				blur->save_pixels[i] = *(int *)&src[(y * width + x - blur->kernel_centre + i) * blur->rgb_size];
				fill_kernel_colors(blur, colors, i);
				i++;
			}
			*(int *)&dest[blur_index] = pack_color_channels((int)colors[0], (int)colors[1], (int)colors[2], (int)colors[3]);
			x++;
		}
		y++;
	}
}


int	window_update_clock(t_win *win)
{
	ftime(&win->blur.clock.end);
	win->blur.clock.elapsed = (size_t) (1000.0 * (win->blur.clock.end.time - win->blur.clock.start.time)
	+ (win->blur.clock.end.millitm - win->blur.clock.start.millitm));
	win->blur.clock.start = win->blur.clock.end;
	//printf("clock says %u elapsed\n", win->blur.clock.elapsed);
	return (win->blur.clock.elapsed + 1);
}



static float pause_gaussian(float x, float sigma) {
    return exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * MY_PI) * sigma);
}

// Function to create a Gaussian kernel of size N with standard deviation sigma
static void pause_setup_kernel(t_pause_blur *blur)
{
	int 	i;
	float 	sum;

	sum = 0;
	i = 0;
	while (i < blur->kernel_size)
	{
        blur->kernel[i] = pause_gaussian(i - blur->kernel_centre, sqrt(blur->cur_sigma));
        sum += blur->kernel[i];	
		i++;	
	}
	i = 0;
	while (i < blur->kernel_size)
	{
		blur->kernel[i] /= sum;
		i++;
	}
}

void	blur_pause(t_win *win, t_pause_blur *blur, bool increase_blur)
{
	if (increase_blur)
		blur->elapsed = int_clamp(blur->elapsed + window_update_clock(win), 0, blur->pause_time);
	else
		blur->elapsed = int_clamp(blur->elapsed - window_update_clock(win), 0, blur->pause_time);
	blur->cur_sigma = blur->min_sigma + (int)(((float)blur->elapsed / (float)blur->pause_time) * (blur->max_sigma - blur->min_sigma));
	//printf("sigma is %d, elapsed is %ld\n", blur->cur_sigma, blur->elapsed);
	pause_setup_kernel(blur);
	blur_horizontal(blur, blur->first, blur->save_front, blur->width, blur->height);
	window_transpose(blur->second, blur->first, blur->width, blur->height, blur->rgb_size);
	blur_horizontal(blur, blur->first, blur->second, blur->height, blur->width);
	window_transpose(blur->second, blur->first, blur->height, blur->width, blur->rgb_size);
	dump_blur_to_front_buf(win, blur, blur->second);
}

void	window_pause_manager(t_win *win, e_pause_state state, bool blur_on)
{
	t_pause_blur *blur;

	blur = &win->blur;
	if (state == PAUSE_ON)
	{
		if (blur->elapsed >= blur->pause_time)
		{
			blur->elapsed = blur->pause_time;
			//printf("hello?\n");
			return ;
		}
		if (blur->elapsed <= 0)
		{
			ft_memcpy(blur->save_front, win->front_buf, win->height * win->width * win->rgb_size);
			window_update_clock(win);
			blur->elapsed = 1;
		}
		//printf("blur elapsed on %d\n", blur->elapsed);
		if (blur_on)
			blur_pause(win, blur, true);
		else
			blur->elapsed = int_clamp(blur->elapsed + window_update_clock(win), 0, blur->pause_time);;
	}
	else if (state == PAUSE_OFF)
	{
		//printf("elapsed off is %d\n", blur->elapsed);
		if (blur->elapsed <= 0)
		{
			blur->elapsed = 0;
			return ;
		}
		if (blur->elapsed >= blur->pause_time)
		{
			blur->elapsed = blur->pause_time;
			window_update_clock(win);
		}
			
		//printf("blur elapsed off %d\n", blur->elapsed);
		if (blur_on)
			blur_pause(win, blur, false);
		else
			blur->elapsed = int_clamp(blur->elapsed - window_update_clock(win), 0, blur->pause_time);
	}
}
