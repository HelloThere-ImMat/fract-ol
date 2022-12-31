/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:20:35 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/30 21:31:07 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//IMPORTANT
	//		printf is used, need to use my own ft_prinft

//		Challenges :
//	Code for julia's fractal
//	Find graphic optimization techniques
//	Improve Color_Pallette to make it continuous
//	BONUS : Essayer de coder le triangle de Sierpinski



void get_syst(t_data *data)
{
	data->Xmin = XMIN;
	data->Xmax = XMAX;
	data->Ymin = YMAX;
	data->Ymax = YMIN;
}

int	 handle_mouse_input(int mousesym, int i, int j, t_data *data)
{
	float x;
	float y;

	x = get_syst_pos(i, 0, data);
	y = get_syst_pos(j, 1, data);

	// printf("y is %0.6f", y);
	// //5 is zoom in / two fingers UP
	// printf("mousesym = %d\n", mousesym);

	// printf("OLD xmax = %0.8f\n", data->Xmax);
	// printf("OLD xmin = %0.8f\n", data->Xmin);
	// printf("OLD ymin = %0.8f\n", data->Ymax);
	// printf("OLD ymax = %0.8f\n", data->Ymin);
	if (mousesym == 1)
	{
		data->Xmin = get_new_border(x, y, ZOOM_IN_XMIN, data);
		data->Xmax = get_new_border(x, y, ZOOM_IN_XMAX, data);
		data->Ymin = get_new_border(x, y, ZOOM_IN_YMIN, data);
		data->Ymax = get_new_border(x, y, ZOOM_IN_YMAX, data);
	}
	//4 is zoom out / two fingers down
	if (mousesym == 2)
	{
		data->Xmin = get_new_border(x, y, ZOOM_OUT_XMIN, data);
		data->Xmax = get_new_border(x, y, ZOOM_OUT_XMAX, data);
		data->Ymin = get_new_border(x, y, ZOOM_OUT_YMIN, data);
		data->Ymax = get_new_border(x, y, ZOOM_OUT_YMAX, data);
	}

	// printf("NEW xmax = %0.8f\n", data->Xmax);
	// printf("NEW xmin = %0.8f\n", data->Xmin);
	// printf("NEW ymin = %0.8f\n", data->Ymax);
	// printf("NEW ymax = %0.8f\n", data->Ymin);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &(*data).img.bpp, &(*data).img.line_len, &(*data).img.endian);
	render(data);

	return (0);
}

int handle_key_input(int keycode, t_data *data)
{
	float step;

	step = data->Xmax - data->Xmin;
	step /= 4;

	if (keycode == ESCAPE)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		free(data->mlx_ptr);
		printf("DESTROYED ;)\n");
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
	return (0);
}

int main (int argc, char **argv)
{
	t_data	data;
//get fractal type from argv and store into a int (+ constant values if julia)
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
	mlx_hook(data.win_ptr, KEY_RELEASE, 0, &handle_key_input, &data);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, CLOSE_WINDOW, 0, &quit_window, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
