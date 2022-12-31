#ifndef FRACTOL_H
# define FRACTOL_H


# include <stdlib.h>
# include <stdio.h>
//# include <X11/X.h>
//# include <X11/keysym.h>

# include "minilibx-linux/mlx.h"

//WINDOW

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800

//SYSTEM

# define XMIN -3
# define XMAX 3
# define YMIN -2
# define YMAX 2

//COLORS

# define BLACK 0x000000
# define WHITISH 0xFFEFFF
# define GREEN 0x80C9FF
# define BLUE 0x0000F0
# define DARK_BLUE 0x00006F
# define BLACK_BLUE 0x00001F

//KEYCODE

# define CLOSE_WINDOW 17
# define KEY_RELEASE 2

# define UP_ARROW 125
# define DOWN_ARROW 126
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define ESCAPE 53

//Border & zoom
# define ZOOM_IN_XMIN 1
# define ZOOM_IN_XMAX 2
# define ZOOM_IN_YMIN 3
# define ZOOM_IN_YMAX 4
# define ZOOM_OUT_XMIN 5
# define ZOOM_OUT_XMAX 6
# define ZOOM_OUT_YMIN 7
# define ZOOM_OUT_YMAX 8

# define ZOOM_RATIO 0.25


# define MAX_ITERATION 80

# define MLX_ERROR 1

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define WHITE_PIXEL 0xFFFFFF

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

//typedef struct s_color
//{
//	int	red;
//	int	green;
//	int	bleu;
//}	t_color;

typedef struct s_data
{
	int fractal;
	void *mlx_ptr;
	void *win_ptr;
	t_img img;
	double Xmin;
	double Xmax;
	double Ymin;
	double Ymax;
	float Cx;
	float Cy;
}	t_data;



typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

//graphic shit

void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_img *img, int color);
int render_rect(t_img *img, t_rect rect);
int render_set(t_img *img, t_data *data);
int	render(t_data *data);
void	image_init(t_data *data);
int quit_window(t_data *data);

//MAIN

int handle_input(int keysym, t_data *data);

void get_syst(t_data *data);
int main ();

//math shit

int color_julia(float x, float y, float cx, float cy);
int	color_mandelbrot(float x, float y);
int color_palette(int iteration);
int color_main(int i, int j, t_data *data);
float get_syst_pos(int x, int axis, t_data *data);
float get_new_border(float x, float y, int type, t_data *data);

//fract-ol_utils

int		ft_strcmp(char *s1, char *s2);
int		check_arg(int argc, char **argv, t_data *data);
void	print_error(int error_type);


#endif
