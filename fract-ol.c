/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:20:35 by mdorr             #+#    #+#             */
/*   Updated: 2023/01/26 17:37:59 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//IMPORTANT
	//		printf is used, need to use my own ft_prinft

//		Challenges :
//	BONUS : Essayer de coder le triangle de Sierpinski

void	get_syst(t_data *data)
{
	data->xmin = XMIN;
	data->xmax = XMAX;
	data->ymin = YMAX;
	data->ymax = YMIN;
	data->color = 3;
}

int	handle_mouse_input(int mousesym, int i, int j, t_data *data)
{
	double	x;
	double	y;

	x = get_syst_pos(i, 0, data);
	y = get_syst_pos(j, 1, data);
	if (mousesym == 4)
	{
		data->xmin = get_new_border(x, y, ZOOM_IN_XMIN, data);
		data->xmax = get_new_border(x, y, ZOOM_IN_XMAX, data);
		data->ymin = get_new_border(x, y, ZOOM_IN_YMIN, data);
		data->ymax = get_new_border(x, y, ZOOM_IN_YMAX, data);
	}
	if (mousesym == 5)
	{
		data->xmin = get_new_border(x, y, ZOOM_OUT_XMIN, data);
		data->xmax = get_new_border(x, y, ZOOM_OUT_XMAX, data);
		data->ymin = get_new_border(x, y, ZOOM_OUT_YMIN, data);
		data->ymax = get_new_border(x, y, ZOOM_OUT_YMAX, data);
	}
	render(data);
	return (0);
}

void	handle_arrow_input(int keycode, t_data *data)
{
	double	step;

	step = data->xmax - data->xmin;
	step /= 4;
	if (keycode == UP_ARROW)
	{
		data->ymax += step;
		data->ymin += step;
	}
	if (keycode == DOWN_ARROW)
	{
		data->ymax -= step;
		data->ymin -= step;
	}
	if (keycode == LEFT_ARROW)
	{
		data->xmax -= step;
		data->xmin -= step;
	}
	if (keycode == RIGHT_ARROW)
	{
		data->xmax += step;
		data->xmin += step;
	}
}

int	handle_key_input(int keycode, t_data *data)
{
	if (keycode == ESCAPE)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		data->win_ptr = NULL;
		free(data->mlx_ptr);
		write(1, "DESTROYED\n", 10);
		exit(EXIT_SUCCESS);
	}
	if (keycode == C_KEY)
		data->color++;
	if (keycode == SPACE_KEY)
	{
		data->xmin = XMIN;
		data->xmax = XMAX;
		data->ymin = YMAX;
		data->ymax = YMIN;
	}
	handle_arrow_input(keycode, data);
	render(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_arg(argc, argv, &data) == 0)
		return (0);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "fract-ol");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	get_syst(&data);
	image_init(&data);
	mlx_mouse_hook(data.win_ptr, &handle_mouse_input, &data);
	mlx_hook(data.win_ptr, KEY_PRESS, KeyPressMask, &handle_key_input, &data);
	mlx_hook(data.win_ptr, CLOSE_WINDOW, LeaveWindowMask, &quit_window, &data);
	render(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
