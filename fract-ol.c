/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:20:35 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/23 16:58:13 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void get_syst(t_data *data)
{
	data->Xmin = -3;
	data->Xmax = 3;
	data->Ymin = -3;
	data->Ymax = 3;
}

int render_set(t_img *img, t_data *data)
{
	int i;
	int j;

	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		i = 0;
		while  (i < WINDOW_WIDTH)
		{
			img_pix_put(img, i, j, color_main(i, j, data));
			i++;
		}
		j++;
	}
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	render_set(&data->img, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int handle_key_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	 handle_mouse_input(int mousesym, int i, int j, t_data *data)
{
	float x;
	float y;
	float ixmin;
	float ixmax;
	float iymin;
	float iymax;



	x = get_syst_pos(i, 0, data);
	y = get_syst_pos(j, 1, data);
	printf("x : %0.2f, y : %0.2f\n", x, y);
	if (mousesym == 4)
	{
		printf("bla\n");
		ixmin = data->Xmin + 10/100 * x;
		ixmax = data->Xmax - 10/100 *(data->Xmax - x);
		iymin = data->Ymin + 10/100 * y;
		iymax = data->Ymax - 10/100 *(data->Ymax - y);
		printf("Xmin : %0.2f\n", ixmin);
	}
	if (mousesym == 5)
	{
		ixmin = data->Xmin - 10/100 * x;
		ixmax = data->Xmax + 10/100 *(data->Xmax - x);
		ixmin = data->Ymin - 10/100 * y;
		ixmax = data->Ymax + 10/100 *(data->Ymax - y);
	}

	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &(*data).img.bpp, &(*data).img.line_len, &(*data).img.endian);
	render(data);

	return (0);
}

int	 handle_mouse_input2(int mousesym, int i, int j, t_data *data)
{
	if (mousesym == 4)
	{
		data->Xmin /= 2;
		data->Xmax /= 2;
		data->Ymin /= 2;
		data->Ymax /= 2;
	}
	if (mousesym == 5)
	{
		data->Xmin *= 2;
		data->Xmax *= 2;
		data->Ymin *= 2;
		data->Ymax *= 2;
	}
	printf("xmax = %0.2f\n", data->Xmax);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &(*data).img.bpp, &(*data).img.line_len, &(*data).img.endian);
	render(data);

	return (0);
}

void	image_init(t_data *data)
{
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &(*data).img.bpp, &(*data).img.line_len, &(*data).img.endian);
}

int main ()
{
	t_data	data;


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
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_key_input, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);

	free(data.mlx_ptr);
}
