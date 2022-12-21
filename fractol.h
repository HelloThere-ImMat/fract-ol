#ifndef FRACTOL_H
# define FRACTOL_H


# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000

# define XMIN -3
# define XMAX 3
# define YMIN -3
# define YMAX 3

# define MAX_ITERATION 50

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
	void *mlx_ptr;
	void *win_ptr;
	t_img img;
	float Xmin;
	float Xmax;
	float Ymin;
	float Ymax;
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

//Graphic Requirements

void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_img *img, int color);
int render_rect(t_img *img, t_rect rect);
int render_set(t_img *img, t_data *data);
int	render(t_data *data);
int handle_input(int keysym, t_data *data);
void get_syst(t_data *data);
int main ();

//Math shit

int	color_mandelbrot(float x, float y);
int color_palette(int iteration);
int color_main(int i, int j, t_data *data);


#endif
