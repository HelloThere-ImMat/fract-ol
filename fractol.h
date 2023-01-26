/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:30:58 by mdorr             #+#    #+#             */
/*   Updated: 2023/01/26 17:39:36 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx/mlx.h"

//WINDOW

# define W_WIDTH 1200
# define W_HEIGHT 800

//SYSTEM

# define XMIN -3
# define XMAX 3
# define YMIN -2
# define YMAX 2

//COLORS

# define BLACK 0x000000
# define BLACK_BLUE 0x00001F

//KEYCODE MAC

//# define CLOSE_WINDOW 17
//# define KEY_PRESS 2

//# define UP_ARROW 125
//# define DOWN_ARROW 126
//# define LEFT_ARROW 123
//# define RIGHT_ARROW 124
//# define ESCAPE 53

//# define C_KEY 8
//# define SPACE_KEY 49

//KEYCODE LINUX

# define CLOSE_WINDOW 17
# define KEY_PRESS 2
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define ESCAPE 65307
# define C_KEY 99
# define SPACE_KEY 32

//BORDER & ZOOM

# define ZOOM_IN_XMIN 1
# define ZOOM_IN_XMAX 2
# define ZOOM_IN_YMIN 3
# define ZOOM_IN_YMAX 4
# define ZOOM_OUT_XMIN 5
# define ZOOM_OUT_XMAX 6
# define ZOOM_OUT_YMIN 7
# define ZOOM_OUT_YMAX 8

# define ZOOM_RATIO 0.25
# define MAX_ITERATION 120
# define MLX_ERROR 1

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	int		fractal;
	int		color;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
	double	xold;
	double	yold;
	double	xnew;
	double	ynew;
	float	cx;
	float	cy;
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

//GRAPHIC SHIT

void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_img *img, int color);
void	image_init(t_data *data);
int		render_rect(t_img *img, t_rect rect);
int		render_set(t_img *img, t_data *data);
int		render(t_data *data);
int		quit_window(t_data *data);

//MAIN

int		handle_input(int keysym, t_data *data);
int		main(int argc, char **argv);
void	get_syst(t_data *data);

//MATH SHIT

int		color_julia(float x, float y, t_data *data);
int		color_mandelbrot(float x, float y, t_data *data);
int		color_palette(int iteration, t_data *data);
int		color_main(int i, int j, t_data *data);
float	get_new_border(float x, float y, int type, t_data *data);

//FRACT-OL UTILS

int		ft_strcmp(char *s1, char *s2);
int		check_arg(int argc, char **argv, t_data *data);
void	print_error(int error_type);
float	get_syst_pos(int x, int axis, t_data *data);

//STR UTILS

float	ft_atof(char *nptr);
int		get_sign(char *nptr, int *a);

#endif
