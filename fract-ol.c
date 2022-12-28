/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:20:35 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/28 16:22:26 by mdorr            ###   ########.fr       */
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
	data->Xmin = -3;
	data->Xmax = 3;
	data->Ymin = -3;
	data->Ymax = 3;
}

int	 handle_mouse_input(int mousesym, int i, int j, t_data *data)
{
	float x;
	float y;

	x = get_syst_pos(i, 0, data);
	y = get_syst_pos(j, 1, data);

	// -y unused in the get_new_border func, why ?

	if (mousesym ==4)
	{
		data->Xmax = get_new_border(x, y, 1, data);
		data->Xmin = get_new_border(x, y, 2, data);
		data->Ymax = get_new_border(x, y, 3, data);
		data->Ymin = get_new_border(x, y, 4, data);
	}

	if (mousesym == 5)
	{
		data->Xmax = get_new_border(x, y, 5, data);
		data->Xmin = get_new_border(x, y, 6, data);
		data->Ymax = get_new_border(x, y, 7, data);
		data->Ymin = get_new_border(x, y, 8, data);
	}

	// printf("xmax = %0.8f\n", data->Xmax);
	// printf("xmin = %0.8f\n", data->Xmin);
	// printf("ymin = %0.8f\n", data->Ymax);
	// printf("ymax = %0.8f\n", data->Ymin);
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
