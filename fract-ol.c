/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:20:35 by mdorr             #+#    #+#             */
/*   Updated: 2023/01/25 15:15:24 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//IMPORTANT
	//		printf is used, need to use my own ft_prinft

//		Challenges :
//	BONUS : Essayer de coder le triangle de Sierpinski

void get_syst(t_data *data)
{
	data->Xmin = XMIN;
	data->Xmax = XMAX;
	data->Ymin = YMAX;
	data->Ymax = YMIN;
	data->color = 3;
}

int	 handle_mouse_input(int mousesym, int i, int j, t_data *data)
{
	double x;
	double y;

	x = get_syst_pos(i, 0, data);
	y = get_syst_pos(j, 1, data);

	if (mousesym == 4)
	{
		data->Xmin = get_new_border(x, y, ZOOM_IN_XMIN, data);
		data->Xmax = get_new_border(x, y, ZOOM_IN_XMAX, data);
		data->Ymin = get_new_border(x, y, ZOOM_IN_YMIN, data);
		data->Ymax = get_new_border(x, y, ZOOM_IN_YMAX, data);
	}
	if (mousesym == 5)
	{
		data->Xmin = get_new_border(x, y, ZOOM_OUT_XMIN, data);
		data->Xmax = get_new_border(x, y, ZOOM_OUT_XMAX, data);
		data->Ymin = get_new_border(x, y, ZOOM_OUT_YMIN, data);
		data->Ymax = get_new_border(x, y, ZOOM_OUT_YMAX, data);
	}
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &(*data).img.bpp, &(*data).img.line_len, &(*data).img.endian);
	render(data);
	return (0);
}

int handle_key_input(int keycode, t_data *data)
{
	double step;

	step = data->Xmax - data->Xmin;
	step /= 4;
	if (keycode == ESCAPE)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		free(data->mlx_ptr);
		write(1, "DESTROYED\n", 10);
		exit(EXIT_SUCCESS);
	}
	if (keycode == UP_ARROW)
	{
		data->Ymax += step;
		data->Ymin += step;
	}
	if (keycode == DOWN_ARROW)
	{
		data->Ymax -= step;
		data->Ymin -= step;
	}
	if (keycode == LEFT_ARROW)
	{
		data->Xmax -= step;
		data->Xmin -= step;
	}
	if (keycode == RIGHT_ARROW)
	{
		data->Xmax += step;
		data->Xmin += step;
	}
	if (keycode == C_KEY)
		data->color++;
	if (keycode == SPACE_KEY)
	{
		data->Xmin = XMIN;
		data->Xmax = XMAX;
		data->Ymin = YMAX;
		data->Ymax = YMIN;
	}
	render(data);
	return (0);
}

int main (int argc, char **argv)
{
	t_data	data;
//0  - Julia
//1  - Mandelbrot
	if (check_arg(argc, argv, &data) == 0)
		return (0);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	get_syst(&data);
	image_init(&data);
	mlx_mouse_hook(data.win_ptr, &handle_mouse_input, &data);
	mlx_hook(data.win_ptr, KEY_PRESS, KeyPressMask, &handle_key_input, &data);
	//mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, CLOSE_WINDOW, LeaveWindowMask, &quit_window, &data);
	render(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}